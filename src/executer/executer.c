/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 15:07:21 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/24 11:35:31 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		executer_multi(t_scmd *cmd, t_data *data, int i);
int		executer_single(t_scmd *cmd, t_data *data);

/*wait exit status of last process*/
int	wait_function(pid_t child, int i, t_data *data)
{
	int status;
	
	if (i == data->n_pipes)
	{
		waitpid(child, &status, 0);
		if (status != 0)
		{
			printf("execve error process i = %d\n", i);
			return (0);
		}
	}
	return (1);
}

int heredoc(t_data *data, t_scmd *cmd, int i);
int destroy_heredoc(t_scmd *cmd);

/*if n_pipes present call multi command, otherwise single*/
int executer(t_scmd *cmd, t_data *data)
{
	int		i;
	t_scmd	*ptr;

	data->cmd_path = 0;
	data->envp_ar = 0;
	data->cmd_args = 0;
	ptr = cmd;
	if (!heredoc(data, cmd, 0))
		return (0);
	if (data->n_pipes)
	{
		i = 0;
		while (cmd)
		{
			if (!executer_multi(cmd, data, i))
				return (0);
			cmd = cmd->next_cmd;
			i++;
		}
	}
	else
	{
		if (!executer_single(cmd, data))
			return (0);
	}
	destroy_heredoc(ptr);
	return (1);
}
