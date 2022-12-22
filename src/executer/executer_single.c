/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer_single.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/22 12:38:58 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/22 12:42:42 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		wait_function(pid_t child, int i, t_data *data);
int		execve_param(t_scmd *cmd, t_data *data);
void	free_execve_param(t_data *data);
int 	save_std_fd(int *in, int *out);
int		reset_std_fd(int in, int out);

int	wait_function(pid_t child, int i, t_data *data);

/*set redirection, call execve*/
int	child_process_single(t_scmd *cmd, t_data *data)
{
	if ((data->to_close != -1))
	{
		if(close(data->to_close) == -1)
			exit (0);
	}
	if (!set_red(cmd->file, data))
		exit(0);//open or close error
	execve(data->cmd_path, data->cmd_args, data->envp_ar);
	return (0);
}

/*fork a child process, call execution of single cmd*/
int	exec_in_child_single(t_scmd *cmd, t_data *data)
{
	pid_t	child;

	child = fork();
	if (child == 0) //child
	{
		child_process_single(cmd, data);
	}
	else if (child > 0) //parent
	{
		if (!wait_function(child, 0, data))
			return (0);
	}
	else if (child < 0)
		return (0); //error
	return (1);
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
			return (0); //error in dup
		ret = execute_builtin(cmd, data);
		if(!reset_std_fd(saved_in, saved_out))
			return (0); //error in dup2
	}
	else
	{
		if(!execve_param(cmd, data))
			return(0);
		ret = exec_in_child_single(cmd, data);
		free_execve_param(data);
	}
	return (ret);
}
