/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 13:56:32 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/02 17:10:10 by lisa          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	type_recogn(char *word)
{
	if (!ft_strncmp(word, "|", 2))
		return (PIPE);
	else if (!ft_strncmp(word, "<", 2))
		return (REDI);
	else if (!ft_strncmp(word, ">", 2))
		return (REDO);
	else if (!ft_strncmp(word, ">>", 3))
		return (REDOA);
	else if (!ft_strncmp(word, "<<", 2))
		return (HEREDOC);
	else
		return (WORD);
}

int	is_redirection(char *c)
{
	if ((*c == '<' && *(c + 1) != '<') || (*c == '>' && *(c + 1) != '>'))
		return (1);
	else if ((*c == '<' && *(c + 1) == '<') || (*c == '>' && *(c + 1) == '>'))
		return (2);
	else if (*c == '$' && *(c + 1) == '?')
		return (2);
	return (0);
}

void	quote_check(int *quote, int *dquote, int c)
{
	if (c == '\'')
	{
		if (*quote == 0)
			*quote = 1;
		else
			*quote = 0;
	}
	else if (c == '\"')
	{
		if (*dquote == 0)
			*dquote = 1;
		else
			*dquote = 0;
	}
}

int	is_space(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ' || c == '\n')
		return (1);
	return (0);
}
