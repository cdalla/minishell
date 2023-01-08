/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/29 19:46:09 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/08 16:00:01 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>

/*open the outfile*/
int	set_outfile(t_file *file, t_data *data)
{
	if (data->to_write != -1)
	{
		if (close(data->to_write) == -1)
			return (print_err_msg(errno, file->filename));
	}
	if (file->type == APPEND)
	{
		data->to_write = open(file->filename, O_WRONLY
				| O_APPEND | O_CREAT, 0777);
		if (data->to_write == -1)
			return (print_err_msg(errno, file->filename));
	}
	else
	{
		data->to_write = open(file->filename, O_WRONLY | O_CREAT, 0777);
		if (data->to_write == -1)
			return (print_err_msg(errno, file->filename));
	}
	return (0);
}

/*open infile*/
int	set_infile(t_file *file, t_data *data)
{
	if (data->to_read != -1)
	{
		if (close(data->to_read) == -1)
			return (print_err_msg(errno, file->filename));
	}
	data->to_read = open(file->filename, O_RDONLY);
	if (data->to_read == -1)
		return (print_err_msg(errno, file->filename));
	return (0);
}

/*dup2 of correct fd and then close it*/
int	dup_close(t_data *data)
{
	if (data->to_read != -1)
	{
		if (dup2(data->to_read, STDIN_FILENO) == -1)
			return (print_err_msg(errno, ""));
		if (close(data->to_read) == -1)
			return (print_err_msg(errno, ""));
	}
	if (data->to_write != -1)
	{
		if (dup2(data->to_write, STDOUT_FILENO) == -1)
			return (print_err_msg(errno, ""));
		if (close(data->to_write) == -1)
			return (print_err_msg(errno, ""));
	}
	return (0);
}

/*loop file list and call open file funct*/
int	set_red(t_file *ptr, t_data *data)
{
	int	ret;
	t_file *file;

	file = ptr;
	while (file)
	{
		if (file->type == READ || file->type == HEREDOC)
		{
			ret = set_infile(file, data);
			if (ret)
				return (ret);
		}
		else
		{
			ret = set_outfile(file, data);
			if (ret)
				return (ret);
		}
		file = file->next;
	}
	ret = dup_close(data);
	if (ret)
		return (ret);
	return (0);
}
