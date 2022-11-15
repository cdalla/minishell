/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 13:56:32 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/15 15:39:53 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	type_recogn(char *word)
{
	if (!ft_strncmp(word, "||", 3))
		return (PIPE);
	else if (!ft_strncmp(word, "<", 2))
		return (REDI);
	else if (!ft_strncmp(word, ">", 2))
		return (REDO);
	else if (!ft_strncmp(word, ">>", 3))
		return (REDOA);
	else if (!ft_strncmp(word, "<<", 2))
		return (HERED);
	else
		return (WORD);
}

int quote_check(int value)
{
	if (value == 0)
		return (1);
	return (0);
}

int	is_space(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ' || c == '\n')
		return (1);
	return (0);
}
