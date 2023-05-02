/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer_single.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/22 12:38:58 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/05/03 01:08:23 by lisa          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		wait_function(pid_t child, t_data *data);
int		execve_param(t_scmd *cmd, t_data *data);
int		save_std_fd(int *in, int *out);
int		reset_std_fd(int in, int out);
void	free_execve_param(t_data *data);
void	signals_child(void);

/*set redirection, call execve*/
int	child_process_single(t_scmd *cmd, t_data *data)
{
	int	ret;

	signals_child();
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

	ret = execve_param(cmd, data);
	if (ret)
	{
		free_execve_param(data);
		return (print_err_msg(ret, cmd->cmd_name->value));
	}
	child = fork();
	if (child == 0)
		child_process_single(cmd, data);
	else if (child < 0) //probably have to free param
		return (errno);
	free_execve_param(data);
	return (wait_function(child, data));
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
	// {
	// 	ret = execve_param(cmd, data);
	// 	if (ret)
	// 	{
	// 		free_execve_param(data);
	// 		return (print_err_msg(ret, cmd->cmd_name->value));
	// 	}
	ret = exec_in_child_single(cmd, data);
	// 	free_execve_param(data);
	// }
	return (ret);
}
