/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 15:07:21 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/17 19:42:45 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_fd(t_data *data, int fd[2][2], int i);
int		set_red(t_scmd *cmd, t_data *data);
void	parent_close(int fd[2][2], int i, int n_pipes);

/*translate necessary list in array[], set red, execve with right info*/
int	cmd_start(t_scmd *cmd, t_data *data)//probable leak in the 3 function malloced, path
{
	char	*cmd_path;
	char	**envp_ar;
	char	**cmd_args;

	if (data->to_close != -1)
		close(data->to_close);
	if (!set_red(cmd, data))
		printf("redirection error\n");
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

/*fork a child process, call execution of single cmd*/
int	executer_single(t_scmd *cmd, t_data *data, int i, int multi)//need to call builtins here
{
	pid_t	child;
	int		status;

	child = fork();
	if (child == 0)
	{
		if (multi)
		{
			if(is_builtins(cmd, data, 0))
				exit(0);
		}
		cmd_start(cmd, data);
	}
	else if (child > 0)
	{
		if (i == data->n_pipes)
			waitpid(child, &status, 0);
	}
	else if (child < 0)
	{
		printf("child error\n");
		return (0); //error
	}
	return (1);
}

/*set pipes, set fd, call execution of every command, close fd*/
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
		if (!executer_single(ptr, data, i, 1))
				return (0);
		parent_close(fd, i, data->n_pipes);
		ptr = ptr->next_cmd;
		i++;
	}
	return (1);// success
}

/*if n_pipes present call multi command, otherwise single*/
int executer(t_scmd *cmd, t_data *data)
{
	int	saved_out;
	int saved_in;

	if (data->n_pipes)
		executer_multi(cmd, data);
	else
	{
		saved_in = dup(STDIN_FILENO);
		saved_out = dup(STDOUT_FILENO);
		data->to_close = -1;
		data->to_read = -1;
		data->to_write = -1;
		if(!is_builtins(cmd, data, 0))
		{
			if(!executer_single(cmd, data , 0, 0))
				return(0);
		}
		else
		{
			dup2(saved_in, STDIN_FILENO);
			dup2(saved_out, STDOUT_FILENO);
		}
	}
	return (1);
}
