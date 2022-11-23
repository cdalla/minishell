/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 15:07:21 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/23 00:54:43 by lisa          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_dsarry(char **array)//just for testing purpose !!!REMOVE!!!
{
	int i = 0;

	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}

int	cmd_start(t_scmd *cmd, t_data *data)
{
	char	*cmd_path;
	char	**envp_ar;
	char	**cmd_args;
	
	// if (cmd->infile)
	// 	//set infiles
	// if (cmd->outfile)
	// 	//set outfile

	cmd_path = check_path_cmd(cmd->cmd_name->value, data);
	if (!cmd_path)
		return (0);
	envp_ar = ls_toarr_env(data->envp);
	if (!envp_ar)
		return (0);
	//print_dsarry(envp_ar); //testing purpose
	cmd_args = ls_toarr_args(cmd->next_arg);
	if (!cmd_args)
		return (0);
	//print_dsarry(cmd_args); //testing purpose
	//execve(cmd_path, cmd_args, envp_ar);
	//execve(check_path_cmd, ls_toarr_env, ls_toarr_args); //this is nice :) do not care about ret
	return (1);
}

int	executer_single(t_scmd *cmd, t_data *data)
{
	//no pipe
	pid_t	child;
	
	child = fork();
	if (child == 0)
	{
		//child task
		cmd_start(cmd, data);
	}
	else if (child > 0)
	{
		//parent wait the child end
		wait(NULL);
	}
	else
		return (0); //error
	return (1);
}

int	executer_multi(t_scmd **cmd_line, t_data *data, int n_pipes)
{
	int	i;

	i = 0;
	while (i <= n_pipes)
	{
		//set fd for pipes
		executer_single(cmd_line[i], data);
		//check execution return
	}
	return (1);// success
}
