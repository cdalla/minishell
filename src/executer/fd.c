/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 09:52:49 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/07 13:27:38 by cdalla-s      ########   odam.nl         */
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
		if (i != 0)
			data->to_read = fd[1][0];
	}
}

/*close correct fd based on index value*/
int	parent_close(int fd[2][2], int i, int n_pipes)
{
	if (i % 2)
	{
		if (i < n_pipes)
		{
			if (close(fd[1][1]) == -1)
				return (print_err_msg(errno, ""));
		}
		if (close(fd[0][0]) == -1)
			return (print_err_msg(errno, ""));
	}
	else
	{
		if (i < n_pipes)
		{
			if (close(fd[0][1]) == -1)
				print_err_msg(errno, "");
		}
		if (i != 0)
		{
			if (close(fd[1][0]) == -1)
				print_err_msg(errno, "");
		}
	}
	return (0);
}

/*save std in and out, return 0 for err*/
int	save_std_fd(int *in, int *out)
{
	*in = dup(STDIN_FILENO);
	if (*in == -1)
		return (0);
	*out = dup(STDOUT_FILENO);
	if (*out == -1)
		return (0);
	return (1);
}

/*reset std in and out, return 0 for error*/
int	reset_std_fd(int in, int out)
{
	if (dup2(in, STDIN_FILENO) == -1)
		return (0);
	if (dup2(out, STDOUT_FILENO) == -1)
		return (0);
	return (1);
}
