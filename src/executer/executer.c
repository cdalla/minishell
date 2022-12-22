/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 15:07:21 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/22 15:40:24 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		executer_multi(t_scmd *cmd, t_data *data, int i);
int		executer_single(t_scmd *cmd, t_data *data);

/*wait exit status of last process*/
int	wait_function(pid_t child, int i, t_data *data)
{
	if (i == data->n_pipes)
	{
		waitpid(child, &status, 0);
		if (status != 0)
		{
			printf("execve error process i = %d\n", i);
			return (0);
		}
		wait(NULL);
	}
	return (1);
}

/*if n_pipes present call multi command, otherwise single*/
int executer(t_scmd *cmd, t_data *data)
{
	int		i;
	t_scmd	*ptr;

	data->cmd_path = 0;
	data->envp_ar = 0;
	data->cmd_args = 0;
	if (data->n_pipes)
	{
		i = 0;
		ptr = cmd;
		while (ptr)
		{
			write(1, ptr->cmd_name->value, ft_strlen( ptr->cmd_name->value));
			write(1, "\n", 1);
			if (!executer_multi(ptr, data, i))
				return (0);
			ptr = ptr->next_cmd;
			i++;
		}
	}
	else
	{
		if (!executer_single(cmd, data))
			return (0);
	}
	return (1);
}
