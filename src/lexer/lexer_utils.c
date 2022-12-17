/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 13:56:32 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/17 22:31:20 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*recognize token type*/
int	type_recogn(char *word)
{
	if (!ft_strncmp(word, "|", 2))
		return (PIPE);
	else if (!ft_strncmp(word, "<", 2))
		return (READ);
	else if (!ft_strncmp(word, ">", 2))
		return (WRITE);
	else if (!ft_strncmp(word, ">>", 3))
		return (APPEND);
	else if (!ft_strncmp(word, "<<", 2))
		return (HEREDOC);
	else
		return (WORD);
}

/*check special character for token trimming*/
int	is_redirection(char *c)
{
	if ((*c == '<' && *(c + 1) != '<') || (*c == '>' && *(c + 1) != '>'))
		return (1);
	else if (*c == '|')
		return (1);
	else if ((*c == '<' && *(c + 1) == '<') || (*c == '>' && *(c + 1) == '>'))
		return (2);
	else if (*c == '$' && *(c + 1) == '?')
		return (2);
	return (0);
}

/*check and set opposite value of quote and dquote*/
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

/*is_space_and_newline*/
int	is_space(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ' || c == '\n')
		return (1);
	return (0);
}
