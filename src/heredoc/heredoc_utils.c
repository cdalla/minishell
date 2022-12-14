/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/06 12:46:05 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/08 16:07:05 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

/*delete all heredoc tmp files created*/
int	destroy_heredoc(t_scmd *cmd)
{
	t_file *ptr;
	while (cmd)
	{
		ptr = cmd->file;
		while (ptr)
		{
			if (ptr->type == HEREDOC)
			{
				if (access(ptr->filename, F_OK) == 0)
					unlink(ptr->filename);
			}
			ptr = ptr->next;
		}
		cmd = cmd->next_cmd;
	}
	return (1);
}

/*write in heredoc file*/
int	write_in_file(int fd, char *del)
{
	char	*str;

	str = NULL;
	while (1)
	{
		if (str)
		{
			free(str);
			str = NULL;
		}
		str = readline(">");
		if (!str || !ft_strncmp(del, str, ft_strlen(del) + 1))
			break ;
		if (write(fd, str, ft_strlen(str)) == -1)
			return (errno);
		write(fd, "\n", 1);
	}
	return (0);
}
