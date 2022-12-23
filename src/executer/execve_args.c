/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve_args.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 13:24:36 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/22 12:32:25 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_envp_array(t_data *data)
{
	int i;
	
	i = 0;
	while(data->envp_ar[i])
	{
		free(data->envp_ar[i]);
		i++;
	}
	free(data->envp_ar);
	data->envp_ar = 0;
}

void	free_cmd_args_array(t_data *data)
{
	int i;
	
	i = 0;
	while(data->cmd_args[i])
	{
		free(data->cmd_args[i]);
		i++;
	}
	free(data->cmd_args);
	data->cmd_args = 0;
}

void	free_execve_param(t_data *data)
{
	if (data->cmd_path)
	{
		free(data->cmd_path);
		data->cmd_path = 0;
	}
	if (data->cmd_args)
		free_envp_array(data);
	if (data->cmd_args)
		free_cmd_args_array(data);
}

/*fill cmdpath, args[], envp[]*/
int	execve_param(t_scmd *cmd, t_data *data)
{
	data->cmd_path = check_path_cmd(cmd->cmd_name->value, data);
	if (!data->cmd_path)
	{
		printf("cmd path error\n");
		return (0); //malloc error
	}
	data->envp_ar = ls_toarr_env(data->envp);
	if (!data->envp_ar)
	{
		printf("envp array error\n");
		free_execve_param(data);
		return (0); //malloc error
	}
	data->cmd_args = ls_toarr_args(cmd->next_arg, data->cmd_path);
	if (!data->cmd_args)
	{
		free_execve_param(data);
		printf("cmd args array error\n");
		return (0); //malloc error
	}
	return (1);
}	