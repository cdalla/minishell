/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 15:07:21 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/02 15:45:38 by lisa          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_fd(t_data *data, int fd[2][2], int i);
int		set_red(t_scmd *cmd, t_data *data);
void	parent_close(int fd[2][2], int i, int n_pipes);

int	cmd_start(t_scmd *cmd, t_data *data)//probable leak in the 3 function malloced, path
{
	char	*cmd_path;
	char	**envp_ar;
	char	**cmd_args;

	if (data->to_close != -1)
		close(data->to_close);
	set_red(cmd, data);
	cmd_path = check_path_cmd(cmd->cmd_name->value, data);
	if (!cmd_path)
		return (0);
	envp_ar = ls_toarr_env(data->envp);
	if (!envp_ar)
		return (0);
	cmd_args = ls_toarr_args(cmd->next_arg, cmd_path);
	if (!cmd_args)
		return (0);
	execve(cmd_path, cmd_args, envp_ar);
	//execve(check_path_cmd, ls_toarr_env, ls_toarr_args); //this is nice :) do not care about ret
	return (0);
}

pid_t	executer_single(t_scmd *cmd, t_data *data, int i)//need to call builtins here
{
	pid_t	child;
	int		status;

	child = fork();
	if (child == 0)
	{
		cmd_start(cmd, data);
	}
	else if (child > 0)
	{
		if (i == data->n_pipes)
		{
			waitpid(child, &status, 0);
			// i = 0;
			// while (i < data->n_pipes)
			// {
			// 	wait(NULL);
			// 	i++;
			// }
		}
	}
	else if (child < 0)
	{
		printf("fork failed\n");
		return (0); //error
	}
	return (child);
}

int	executer_multi(t_scmd *cmd, t_data *data)
{
	t_scmd	*ptr;
	int		fd[2][2];
	int		i;

	i = 0;
	ptr = cmd;
	while(ptr)
	{
		if (i < data->n_pipes)
			pipe(fd[i % 2]);
		set_fd(data, fd, i);
		executer_single(ptr, data, i);
		parent_close(fd, i, data->n_pipes);
		ptr = ptr->next_cmd;
		i++;
	}
	return (1);// success
}

int executer(t_scmd *cmd, t_data *data)
{
	if (data->n_pipes)
		executer_multi(cmd, data);
	else
	{
		data->to_close = -1;
		data->to_read = -1;
		data->to_write = -1;
		executer_single(cmd, data , 0);
	}
	return (0);
}
