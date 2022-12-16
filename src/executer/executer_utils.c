/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 09:52:49 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/16 12:47:54 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*set correct fd for pipes based on index value*/
void	set_fd(t_data *data, int fd[2][2], int i)
{
	data->to_close = -1;
	data->to_read = -1;
	data->to_write = -1;
	if (i % 2)
	{
		if (i < data->n_pipes)
		{
			data->to_close = fd[1][0];
			data->to_write = fd[1][1];
		}
		data->to_read = fd[0][0];
	}
	else
	{
		if (i < data->n_pipes)
		{
			data->to_close = fd[0][0];
			data->to_write = fd[0][1];
		}
		if(i != 0)
			data->to_read = fd[1][0];
	}
}

/*close correct fd based on index value*/
void	parent_close(int fd[2][2], int i, int n_pipes)
{
	if (i % 2)
	{
		if (i < n_pipes)
			close(fd[1][1]);
		close(fd[0][0]);
	}
	else
	{
		if (i < n_pipes)
			close(fd[0][1]);
		if (i != 0)
			close(fd[1][0]);
	}
}

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
