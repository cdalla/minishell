/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/06 12:46:05 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/06 12:49:57 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

/*delete all heredoc tmp files created*/
int destroy_heredoc(t_scmd *cmd)
{
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

/*write in heredoc file*/
int	write_in_file(int fd, char *del)
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
		if (!str || !ft_strncmp(del, str, ft_strlen(del) + 1))
			break ;
		if (write(fd, str, ft_strlen(str)) == -1)
			return(errno);
		write(fd, "\n", 1);
	}
	return (0);
}