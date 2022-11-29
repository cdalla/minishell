/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 15:07:21 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/29 19:47:21 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_dsarry(char **array)//just for testing purpose !!!REMOVE!!!
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}

int	cmd_start(t_scmd *cmd, t_data *data, int *fd)
{
	char	*cmd_path;
	char	**envp_ar;
	char	**cmd_args;
	int		errno;
	//int 	ret;

	set_red(cmd, fd);
	errno = 0;
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

int	executer_single(t_scmd *cmd, t_data *data, int *fd)
{
	pid_t	child;
	int		pouet;

	child = fork();
	if (child == 0)
	{
		//child task
		cmd_start(cmd, data, fd);
	}
	else if (child > 0)
	{
		//parent wait the child end
		wait(&pouet);
		//printf("execve returned %d\n", pouet);
	}
	else
	{
		printf("fork failed\n");
		return (0); //error
	}
	return (1);
}

int	executer_multi(t_scmd *cmd, t_data *data, int *fd)
{
	t_scmd	*ptr;

	ptr = cmd;
	while(ptr)
	{
		pipe(fd);
		executer_single(ptr, data, fd);
		ptr = ptr->next_cmd;
	}
	// wait(NULL);
	return (1);// success
}

int executer(t_scmd *cmd, t_data *data)
{
	int	fd[2];
	//int	p_fd[2];
	
	// fd[0] = STDIN_FILENO; 
	// fd[1] = STDOUT_FILENO;
	if (data->n_pipes)
		executer_multi(cmd, data, fd);
	else
		executer_single(cmd, data, fd);
	return (0);
}
