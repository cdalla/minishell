/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_red.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/29 19:46:09 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/30 12:31:29 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

int	set_outfile(t_outfile *outfile, t_data *data)
{
	while (outfile)
	{
		if (data->to_write != STDOUT_FILENO)
			close(data->to_write);//close fd set previously
		if (outfile->type == APPEND)
		{
			data->to_write = open(outfile->filename, O_WRONLY | O_APPEND);
			if (data->to_write == -1)
				return (0); //error
		}
		if (outfile->type == WRITE)
		{
			data->to_write = open(outfile->filename, O_WRONLY);
			if (data->to_write == -1)
				return (0); //error
		}
		outfile = outfile->next;
	}
	if (data->to_write != -1)
		dup2(data->to_write, STDOUT_FILENO);
	if (data->to_write != STDOUT_FILENO)
		close(data->to_write);
	return (1);
}

int	set_heredoc(char *del, t_data *data)
{
	char	*tmp = "test_file";
	char	*str = NULL;

	data->to_read = open (tmp , O_WRONLY | O_APPEND |  O_CREAT , 0777);
	if (data->to_read == -1)
		return (-1);//file not opened
	else
	{
		while (1)
		{
			if (str) //if read_line is something
			{
				free(str);
				str = NULL;
			}
			str = readline("gimmeheredoc>");
			if (!ft_strcmp(del, str))
				break ;
			write(data->to_read, str, ft_strlen(str));
			write(data->to_read, "\n", 1);
		}
		free(del);
		del = ft_strdup(tmp);//save the tmp char
		if (!del)
			return (0); //error
		close(data->to_read);
	}
	return (1); //success
}

int	set_infile(t_infile *infile, t_data *data)
{
	while (infile)
	{
		if (data->to_read != STDIN_FILENO)
			close(data->to_read);
		if (infile->type == HERED)//check if we need to manage heredoc if something fails before
		{
			data->to_read = set_heredoc(infile->filename, data);
			if (!data->to_read)
				return (0);
		}
		if (infile->type == READ || infile->type == HERED)
		{
			data->to_read = open(infile->filename, O_RDONLY);
			if (data->to_read == -1)
				return (0); //error
		}
		infile = infile->next;
	}
	if (data->to_read != -1)
		dup2(data->to_read, STDIN_FILENO);
	if (data->to_read != 0)
		close(data->to_read);
	// if (infile->type == HERED) //fix this file delete for heredoc
	// 	unlink(infile->filename);
	return (1);
}

int	set_red(t_scmd *cmd, t_data *data)
{
	if (cmd->infile)
		set_infile(cmd->infile, data);
	if (cmd->outfile)
		set_outfile(cmd->outfile, data);
	return (1);
}