/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/29 19:46:09 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/23 11:32:13 by cdalla-s      ########   odam.nl         */
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
			printf("close infile error\n");//close fd set previously
	}
	if (file->type == APPEND)
	{
		data->to_write = open(file->filename, O_WRONLY | O_APPEND | O_CREAT , 0777);
		if (data->to_write == -1)
			return (0); //error
	}
	else
	{
		data->to_write = open(file->filename, O_WRONLY | O_CREAT , 0777);
		if (data->to_write == -1)
			return (0); //error
	}
	return (1);
}

/*open infile*/
int	set_infile(t_file *file, t_data *data)
{
	if (data->to_read != -1)
	{
		if (close(data->to_read) == -1)
			printf("close error infile\n");
	}
	data->to_read = open(file->filename, O_RDONLY);
	if (data->to_read == -1)
	{
		printf("after open %s\n", strerror(errno));
		return (0); //error
	}
	return (1);
}

/*dup2 of correct fd and then close it*/
int	dup_close(t_data *data)
{
	if (data->to_read != -1)
	{
		dup2(data->to_read, STDIN_FILENO);
		close(data->to_read);
	}
	if (data->to_write != -1)
	{
		dup2(data->to_write, STDOUT_FILENO);
		close(data->to_write);
	}
	return (1);
}

/*loop file list and call open file funct*/
int	set_red(t_file *file, t_data *data)
{
	while(file)
	{
		if (file->type == READ || file->type == HEREDOC)
		{
			if (!set_infile(file, data))
				return (0);
		}
		else
		{
			if (!set_outfile(file, data))
				return (0);
		}
		file = file->next;
	}
	dup_close(data);
	return(1);
}