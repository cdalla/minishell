/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/22 18:34:52 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/23 14:11:24 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
	check heredoc redirection
		if heredoc is found create a file and save it
	
	at the end of the command delete heredoc files
*/

void	stop(int signum)
{
	(void)signum;
	exit(0) ;
}

void	signals_heredoc(void)
{
	signal(SIGINT, stop);
	signal(SIGQUIT, SIG_IGN);
}

int	write_in_file(int fd, char **del)
{
	char	*str = NULL;
	
	while (1)
	{
		if (str) //if read_line is something
		{
			free(str);
			str = NULL;
		}
		str = readline(">");
		if (!str || !ft_strncmp(*del, str, ft_strlen(*del) + 1))
			break ;
		if (write(fd, str, ft_strlen(str)) == -1)
			printf("write in heredoc %s\n", strerror(errno));
		write(fd, "\n", 1);
	}
	return (1);
}


/*open a temporary file, write with input save the file*/
int	set_heredoc(char **del, char *filename)
{
	int		fd;

	fd = open(filename , O_WRONLY | O_APPEND |  O_CREAT , 0777);
	if (fd == -1)
		exit (1);//file not opened
	else
	{
		write_in_file(fd, del);
		//free(*del);
		// *del = ft_strdup(filename);//save the tmp char
		// if (!*del)
		// 	return (0); //malloc error
	}
	if(close(fd) == -1)
	{
		printf("error close in heredoc\n");
		exit (1);
	}
	return (1); //success
}

int	fork_heredoc(char **del, char *filename)
{
	pid_t	child;
	int		status;

	child = fork();
	if (child == 0) //child
	{
		signals_heredoc();
		if (!set_heredoc(del, filename))
			exit(0);//i dont know if it returns
		exit(0);
	}
	else if (child > 0) //parent
	{
		waitpid(child, &status, 0);
			return (status);
	}
	else if (child < 0)
		return (0); //error
	return (1);
}

/*create tmp files for all heredocs per command*/
int heredoc(t_data *data, t_scmd *cmd)
{
	char	*filename;
	t_file	*ptr;
	int		i;

	(void) data;
	i = 0;
	while (cmd)
	{
		ptr = cmd->file;
		filename = ft_strjoin("heredoc", ft_itoa(i));
		if (!filename)
			return (0);
		while (ptr)
		{
			if (ptr->type == HEREDOC)
			{
				if (access(filename, F_OK) == 0)
					unlink(filename);
				if (!set_heredoc(&ptr->filename, filename))
					return (0);
				free(ptr->filename);
				ptr->filename = ft_strdup(filename);//save the tmp char
				if (!ptr->filename)
					return (0); //malloc error
			}
			ptr = ptr->next;
		}
		cmd = cmd->next_cmd;
		i++;
	}
	return (1);
}

int destroy_heredoc(t_scmd *cmd)
{
	int i;

	i = 0;
	while (cmd)
	{
		while (cmd->file)
		{
			if (cmd->file->type == HEREDOC)
			{
				if (access(cmd->file->filename, F_OK) == 0)
					unlink(cmd->file->filename);
			}
			cmd->file = cmd->file->next;
		}
		cmd = cmd->next_cmd;
	}
	return (1);
}