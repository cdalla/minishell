/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer_single.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/22 12:38:58 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/06 13:51:04 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		wait_function(pid_t child, int i, t_data *data);
int		execve_param(t_scmd *cmd, t_data *data);
void	free_execve_param(t_data *data);
int 	save_std_fd(int *in, int *out);
int		reset_std_fd(int in, int out);

void	print_dsarry(char **array);

int	wait_function(pid_t child, int i, t_data *data);

void	sigint_child(int signum)
{
	(void)signum;
	exit(128);
}

void	sigquit_child(int signum)
{
	//write(STDERR_FILENO, "Quit: 3\n", 9);
	(void)signum;
	exit(129);
}

void	signals_child(void)
{
	signal(SIGINT, sigint_child);
	signal(SIGQUIT, sigquit_child);
}

/*set redirection, call execve*/
int	child_process_single(t_scmd *cmd, t_data *data)
{
	int ret;
	
	if ((data->to_close != -1))
	{
		if(close(data->to_close) == -1)
			exit(print_err_msg(errno, ""));
	}
	ret = set_red(cmd->file, data);
	if (ret)
		exit(ret);//open or close error or dup2 error
	if (!cmd->cmd_name)
		exit (0);
	execve(data->cmd_path, data->cmd_args, data->envp_ar);
	exit(print_err_msg(errno, cmd->cmd_name->value));
}

/*fork a child process, call execution of single cmd*/
int	exec_in_child_single(t_scmd *cmd, t_data *data)
{
	pid_t	child;
	int		ret;

	ret = 0;
	child = fork();
	if (child == 0) //child
	{
		signals_child();
		child_process_single(cmd, data);
	}
	else if (child > 0) //parent
		ret = wait_function(child, 0, data);
	else if (child < 0)
		return (errno); //error fork
	return (ret);
}

/*builtin->save and reset std_fd, execve->create and free param*/
int	executer_single(t_scmd *cmd, t_data *data)
{
	int	saved_out;
	int saved_in;
	int	ret;

	if (is_builtin(cmd))
	{
		if (!save_std_fd(&saved_in, &saved_out))
			return (print_err_msg(errno, cmd->cmd_name->value)); //error in dup
		ret = execute_builtin(cmd, data);
		if(!reset_std_fd(saved_in, saved_out))
			return (print_err_msg(errno, cmd->cmd_name->value)); //error in dup2
	}
	else
	{
		ret = execve_param(cmd, data);
		if(ret)
		{
			free_execve_param(data);
			return(print_err_msg(ret, cmd->cmd_name->value)); //malloc error
		}
		ret = exec_in_child_single(cmd, data);
		free_execve_param(data);
	}
	return (ret);
}
