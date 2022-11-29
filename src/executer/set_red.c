/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_red.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/29 19:46:09 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/29 19:47:02 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

int	set_outfile(t_outfile *outfile, int *fd)
{
	while (outfile)
	{
		if (fd[1] != STDOUT_FILENO)
			close(fd[1]);//close fd set previously
		if (outfile->type == APPEND)
		{
			fd[1] = open(outfile->filename, O_APPEND);
				if (fd[1] == -1)
			return (0); //error
		}
		if (outfile->type == WRITE)
		{
			fd[1] = open(outfile->filename, O_WRONLY);
				if (fd[1] == -1)
			return (0); //error
		}
		outfile = outfile->next;
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	return (1);
}

int	set_heredoc(char *del, int *fd)
{
	char	*tmp = "test_file";
	char	*str = NULL;

	*fd = open (tmp , O_WRONLY | O_APPEND |  O_CREAT , 0777);
	if (*fd == -1)
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
			if (!strcmp(del, str))
				break ;
			write(fd, str, strlen(str));
			write(fd, "\n", 1);
		}
		free(del);
		del = ft_strdup(tmp);
		if (del)
			return (0); //error
		close(fd);
	}
}

int	set_infile(t_infile *infile, int *fd)
{
	while (infile)
	{
		if (fd[0] != STDIN_FILENO)
			close(fd[0]);
		// if (infile->type == HERED)//check if we need to manage heredoc if something fails before
		// {
		// 	fd[0] = set_heredoc(infile->filename, &fd[0]);
		// 	if (!fd[0])
		// 		return (0);
		// }
		if (infile->type == READ || infile->type == HERED)
		{
			fd[0] = open(infile->filename, O_RDONLY);
				if (fd[0] == -1)
			return (0); //error
		}
		infile = infile->next;
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	if (infile->type == HERED)
		unlink(infile->filename);
	return (1);
}

int	set_red(t_scmd *cmd, int *fd)
{
	close(fd[0]);//close read end inherited by parent
	if (cmd->infile)
		set_infile(cmd->infile, fd);
	if (cmd->outfile)
	{
		close(fd[1]); //close write end inherited by parent
		set_outfile(cmd->outfile, fd);
	}
	return (1);
}