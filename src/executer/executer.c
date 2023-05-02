/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 15:07:21 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/05/03 01:07:42 by lisa          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		executer_multi(t_scmd *cmd, t_data *data, int i);
int		executer_single(t_scmd *cmd, t_data *data);
int		heredoc(t_scmd *cmd);
int		destroy_heredoc(t_scmd *cmd);

/*wait exit status of last process*/
int	wait_function(pid_t child, t_data *data)
{
	// int	exit_child;

	// exit_child = 0;
	// if (i == data->n_pipes)
	// {
	// 	waitpid(child, &exit_child, 0);
	// 	while (wait(NULL))
	// 		continue ;
	// 	if (exit_child == 2)
	// 		return (130);
	// 	else if (exit_child == 3)
	// 	{
	// 		write(2, "Quit: 3\n", 9);
	// 		return (131);
	// 	}
	// 	else if (exit_child != 0)
	// 		return (exit_child / 256);
	// }
	int	status;
	int	exit_child;

	exit_child = -1;
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		exit_child = (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		exit_child = WTERMSIG(status) + 128;
	while (data->n_pipes > 0)
	{
		wait(NULL);
		data->n_pipes--;
	}
	return (exit_child);
}

/*loop cmd and call execution*/
// int	loop_multi_cmd(t_data *data, t_scmd *cmd)
// {
// 	int		i;
// 	int		ret;
// 	int		fd[2][2];
	
// 	i = 0;
// 	ret = 0;
// 	while (cmd)
// 	{
// 		if (i < data->n_pipes)
// 		{
// 			if (pipe(fd[i % 2]) == -1)
// 				return (print_err_msg(errno, cmd->cmd_name->value));
// 		}
// 		set_fd(data, fd, i); //pass fd
// 		ret = set_execve(data, cmd);
// 		if (ret)
// 			return (ret);
// 		ret = executer_multi(cmd, data, i);
// 		if (ret)
// 			break ;
// 		cmd = cmd->next_cmd;
// 		i++;
// 	}
// 	ret = wait_function(data->child, i, data);
// 	return (ret);
// }


// int	executer_multi(t_scmd *cmd, t_data *data, int i)
// {
// 	int		fd[2][2];
// 	int		ret;
// 	int		ret2;
	
// 	// if (i < data->n_pipes)
// 	// {
// 	// 	if (pipe(fd[i % 2]) == -1)
// 	// 		return (print_err_msg(errno, cmd->cmd_name->value));
// 	// }
// 	//set_fd(data, fd, i);
// 	// ret = set_execve(data, cmd);
// 	// if (ret)
// 	// 	return (ret);
// 	ret = exec_in_child_multi(cmd, data, i);
// 	if (!is_builtin(cmd))
// 		free_execve_param(data);
// 	ret2 = parent_close(fd, i, data->n_pipes);
// 	if (ret2)
// 		return (ret2);
// 	return (ret);
// }


int	loop_multi_cmd(t_data *data, t_scmd *cmd, int i);

/*if n_pipes present call multi command, otherwise single*/
int	executer(t_scmd *cmd, t_data *data)
{
	int		ret;
	t_scmd	*ptr;

	data->cmd_path = 0;
	data->envp_ar = 0;
	data->cmd_args = 0;
	ptr = cmd;
	ret = heredoc(ptr);
	if (data->n_pipes && !ret)
		ret = loop_multi_cmd(data, cmd, 0);
	else if (!ret)
		ret = executer_single(cmd, data);
	destroy_heredoc(ptr);
	return (ret);
}
