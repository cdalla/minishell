/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer_single.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/22 12:38:58 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/08 15:52:47 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		wait_function(pid_t child, int i, t_data *data);
int		execve_param(t_scmd *cmd, t_data *data);
int		save_std_fd(int *in, int *out);
int		reset_std_fd(int in, int out);
void	free_execve_param(t_data *data);
void	signals_child(void);

/*set redirection, call execve*/
int	child_process_single(t_scmd *cmd, t_data *data)
{
	int	ret;

	if ((data->to_close != -1))
	{
		if (close(data->to_close) == -1)
			exit(print_err_msg(errno, ""));
	}
	ret = set_red(cmd->file, data);
	if (ret)
		exit(ret);
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
	if (child == 0)
	{
		signals_child();
		child_process_single(cmd, data);
	}
	else if (child > 0)
		ret = wait_function(child, 0, data);
	else if (child < 0)
		return (errno);
	return (ret);
}

/*builtin->save and reset std_fd, execve->create and free param*/
int	executer_single(t_scmd *cmd, t_data *data)
{
	int	saved_out;
	int	saved_in;
	int	ret;

	if (is_builtin(cmd))
	{
		if (!save_std_fd(&saved_in, &saved_out))
			return (print_err_msg(errno, cmd->cmd_name->value));
		ret = execute_builtin(cmd, data);
		if (!reset_std_fd(saved_in, saved_out))
			return (print_err_msg(errno, cmd->cmd_name->value));
	}
	else
	{
		ret = execve_param(cmd, data);
		if (ret)
		{
			free_execve_param(data);
			return (print_err_msg(ret, cmd->cmd_name->value));
		}
		ret = exec_in_child_single(cmd, data);
		free_execve_param(data);
	}
	return (ret);
}
