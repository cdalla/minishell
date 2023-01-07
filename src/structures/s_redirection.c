/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   s_redirection.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 11:38:32 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/07 14:12:14 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_file	*new_file(enum e_token_type type, char *value)
{
	t_file	*new_file;

	new_file = (t_file *)malloc(sizeof(t_file));
	if (!new_file)
		return (0);
	new_file->type = type;
	new_file->next = 0;
	new_file->filename = ft_strdup(value);
	if (!new_file->filename)
		return (0);
	return (new_file);
}

int	add_file(t_scmd *cmd, enum e_token_type type, char *value)
{
	t_file	*new;
	t_file	*ptr;

	if (!cmd || !type || !value)
		return (0);
	new = new_file(type, value);
	if (!new)
		return (0);
	if (!cmd->file)
		cmd->file = new;
	else
	{
		ptr = cmd->file;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	return (1);
}
