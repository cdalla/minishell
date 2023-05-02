/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer_multi.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/22 12:38:41 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/05/03 00:55:10 by lisa          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int		wait_function(pid_t child, t_data *data);
int		execve_param(t_scmd *cmd, t_data *data);
int		parent_close(int fd[2][2], int i, int n_pipes);
void	free_execve_param(t_data *data);
void	set_fd(t_data *data, int fd[2][2], int i);
void	signals_child(void);

/*check if execute builtin or call execve in child*/
int	child_process_multi(t_scmd *cmd, t_data *data)
{
	int	ret;

	signals_child();
	if ((data->to_close != -1))
	{
		if (close(data->to_close) == -1)
			exit(print_err_msg(errno, cmd->cmd_name->value));
	}
	if (is_builtin(cmd))
		exit(execute_builtin(cmd, data));
	else
	{
		ret = set_red(cmd->file, data);
		if (ret)
			exit(ret);
		execve(data->cmd_path, data->cmd_args, data->envp_ar);
	}
	exit(0);
}

/*fork a child need to execute builtin inside*/
// int	exec_in_child_multi(t_scmd *cmd, t_data *data, int i)
// {
// 	pid_t	child;
// 	//int		ret;

// 	(void)i;
// 	//ret = 0;
// 	child = fork();
// 	data->child = child;
// 	if (child == 0)
// 	{
// 		signals_child();
// 		child_process_multi(cmd, data);
// 	}
// 	else if (child > 0)
// 		return (0);
// 	// 	ret = wait_function(child, i, data);
// 	else if (child < 0)
// 		return (0);
// }

/*set param for execve if cmd not a builtin*/
int	set_execve(t_data *data, t_scmd *cmd)
{
	int	ret;

	ret = 0;
	if (!is_builtin(cmd))
	{
		ret = execve_param(cmd, data);
		if (ret)
		{
			free_execve_param(data);
			return (print_err_msg(ret, cmd->cmd_name->value));
		}
	}
	return (ret);
}

/*set pipes, set fd, call execution of every command, close fd*/
// int	executer_multi(t_scmd *cmd, t_data *data, int i, int fd[2][2], pid_t *child)
// {
// 	int		ret;
// 	//pid_t	child;
	
// 	*child = fork();
// 	//data->child = child;
// 	if (*child == 0)
// 	{
// 		signals_child();
// 		child_process_multi(cmd, data);
// 	}
// 	else if (*child < 0)
// 		return (0);
// 	//ret = exec_in_child_multi(cmd, data, i);
// 	if (!is_builtin(cmd))
// 		free_execve_param(data);
// 	// ret = parent_close(fd, i, data->n_pipes);
// 	// if (ret)
// 	// 	return (ret);
// 	return (0);
// }

int	loop_multi_cmd(t_data *data, t_scmd *cmd, int i)
{
	int		ret;
	int		fd[2][2];
	pid_t	child;
	
	while (cmd)
	{
		if (pipe(fd[i % 2]) == -1)
			return (print_err_msg(errno, cmd->cmd_name->value));
		set_fd(data, fd, i);
		ret = set_execve(data, cmd);
		if (ret)
			return (ret);
		child = fork();
		if (child == 0)
			child_process_multi(cmd, data);
		else if (child < 0)
			return (print_err_msg(errno, cmd->cmd_name->value));
		free_execve_param(data);
		ret = parent_close(fd, i, data->n_pipes);
		if (ret)
			return (ret);
		cmd = cmd->next_cmd;
		i++;
	}
	return (wait_function(child, data));
}
