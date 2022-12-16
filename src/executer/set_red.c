/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_red.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/29 19:46:09 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/16 13:02:36 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

/*loop the outfile list and set the correct file or heredoc*/
int	set_outfile(t_outfile *outfile, t_data *data)
{
	while (outfile)
	{
		if (data->to_write != -1)
			close(data->to_write);//close fd set previously
		if (outfile->type == APPEND)
		{
			data->to_write = open(outfile->filename, O_WRONLY | O_APPEND | O_CREAT , 0777);
			if (data->to_write == -1)
				return (0); //error
		}
		if (outfile->type == WRITE)
		{
			data->to_write = open(outfile->filename, O_WRONLY | O_CREAT , 0777);
			if (data->to_write == -1)
				return (0); //error
		}
		outfile = outfile->next;
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

/*loop the infile list and set the correct file or heredoc*/
int	set_infile(t_infile *infile, t_data *data)
{
	while (infile)
	{
		if (data->to_read != -1)
			close(data->to_read);
		if (infile->type == HERED)//check if we need to manage heredoc if something fails before
		{
			if (access("test_file", F_OK) == 0)
				unlink("test_file");
			if (!set_heredoc(&infile->filename, data))
				return (0);
		}
		if (infile->type == READ || infile->type == HERED)
		{
			data->to_read = open(infile->filename, O_RDONLY | O_CREAT , 0777);
			if (data->to_read == -1)
				return (0); //error
		}
		infile = infile->next;
	}
	return (1);
}

/*call infile, outfile check, remove heredoc file, dup2*/
int	set_red(t_scmd *cmd, t_data *data)
{
	if (!set_infile(cmd->infile, data))
		return (0);
	if (data->to_read != -1)
		dup2(data->to_read, STDIN_FILENO);
	close(data->to_read);
	if (access("test_file", F_OK) == 0)
		unlink("test_file");
	if (!set_outfile(cmd->outfile, data))
		return (0);
	if (data->to_write != -1)
		dup2(data->to_write, STDOUT_FILENO);
	close(data->to_write);
	return (1);
}