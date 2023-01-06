/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/22 18:34:52 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/06 12:51:36 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>

int	write_in_file(int fd, char *del);

void	quit(int signum)
{
	(void)signum;
	exit(129) ;
}

void	inter(int signum)
{
	(void)signum;
	exit(128) ;
}

void	signals_heredoc(void)
{
	signal(SIGINT, inter);
	signal(SIGQUIT, quit);
}

/*open a temporary file, write with input save the file*/
int	set_heredoc(char *del, char *filename)
{
	int		fd;
	int		ret;

	ret = 0;
	fd = open(filename , O_WRONLY | O_APPEND |  O_CREAT , 0777);
	if (fd == -1)
		exit (errno);//file not opened
	else
		ret = write_in_file(fd, del);
	if(close(fd) == -1)
		exit (errno);//file not closed
	exit(ret); //success
}

/*fork child process to save heredoc*/
int	fork_heredoc(char *del, char *filename)
{
	pid_t	child;
	int		exit_child;

	exit_child = 0;
	child = fork();
	if (child == 0)
	{
		signals_heredoc();
		set_heredoc(del, filename);
	}
	else if (child > 0)
	{
		waitpid(child, &exit_child, 0);
		if (exit_child != 0)
			return (exit_child / 256);
	}
	else if (child < 0)
		return (errno);
	return (exit_child);
}

/*loop through files and manage heredoc type*/
int	loop_files_heredoc(t_file *ptr, char *filename)
{
	int		ret;
	char	*del;

	ret = 0;
	while (ptr)
	{
		if (ptr->type == HEREDOC)
		{
			if (access(filename, F_OK) == 0)
				unlink(filename);
			del = ft_strdup(ptr->filename);
			if (!del)
				return (108); //malloc fail
			free(ptr->filename);
			ptr->filename = filename;
			ret = fork_heredoc(del, filename); //create file and fill it
			free(del);
			if (ret)
				return (ret);
		}
		ptr = ptr->next;
	}
	return (ret);
}

/*create tmp files for all heredocs per command*/
int heredoc(t_scmd *cmd)
{
	t_file	*ptr;
	int		ret;
	int		i;
	char	*filename;

	ret = 0;
	i = 0;
	while (cmd)
	{
		ptr = cmd->file;
		filename = ft_strjoin("heredoc", ft_itoa(i)); //create filename
		if (!filename)
			return (108);
		ret = loop_files_heredoc(ptr, filename);
		if (ret)
			return (ret);
		cmd = cmd->next_cmd;
		i++;
	}
	return (ret);
}
