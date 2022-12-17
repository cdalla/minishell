/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_red.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/29 19:46:09 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/17 23:10:06 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

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

/*open a temporary file, write with input save the file*/
int	set_heredoc(char **del, t_data *data)
{
	char	*str = NULL;

	data->to_read = open ("test_file" , O_WRONLY | O_APPEND |  O_CREAT , 0777);
	if (data->to_read == -1)
		return (0);//file not opened
	else
	{
		while (1)
		{
			if (str) //if read_line is something
			{
				free(str);
				str = NULL;
			}
			str = readline(">");
			if (!ft_strncmp(*del, str, ft_strlen(*del) + 1))
				break ;
			write(data->to_read, str, ft_strlen(str));
			write(data->to_read, "\n", 1);
		}
		free(*del);
		*del = "test_file";//save the tmp char
		close(data->to_read);
	}
	return (1); //success
}

/*open infile or heredoc*/
int	set_infile(t_file *file, t_data *data)
{
	if (data->to_read != -1)
	{
		if (close(data->to_read) == -1)
			printf("close outfile error\n");
	}
	if (file->type == HEREDOC)//check if we need to manage heredoc if something fails before
	{
		if (access("test_file", F_OK) == 0)
			unlink("test_file");
		if (!set_heredoc(&file->filename, data))
			return (0);
	}
	data->to_read = open(file->filename, O_RDONLY, 0777);
	if (data->to_read == -1)
		return (0); //error
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
	if (access("test_file", F_OK) == 0)
		unlink("test_file");
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
