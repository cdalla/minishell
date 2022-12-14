/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 10:46:17 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/03 15:53:52 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*trim and return single token value*/
int	count_word_len(char **s, int *wl)
{
	char	*word;
	int		quote;
	int		dquote;

	word = 0;
	quote = 0;
	dquote = 0;
	while ((*(*s + *wl) && (!is_space(*(*s + *wl)) || quote || dquote)))
	{
		if (*(*s + *wl) == '\'' || *(*s + *wl) == '\"')
			quote_check(&quote, &dquote, *(*s + *wl));
		if (!quote && !dquote && is_redirection((*s + *wl)))
		{
			(*wl) += is_redirection((*s + *wl));
			break ;
		}
		(*wl)++;
		if ((is_redirection((*s + *wl)) && !quote && !dquote))
			break ;
	}
	if (quote || dquote)
		return (0);
	return (*wl);
}

/*split input into words and put it directly into token list*/
int	tokenize(char *str, t_data *data)
{
	int		w_len;
	char	*word;
	int		type;

	while (*str)
	{
		w_len = 0;
		while (is_space(*str) && *str)
			str++;
		if (ft_strlen(str))
		{	
			if (!count_word_len(&str, &w_len))
				return (108);
			word = ft_substr(str, 0, w_len);
			if (!word)
				return (107);
			type = type_recogn(word);
			if (!add_token(&data->token, word, type))
				return (107);
			str += w_len;
		}
	}
	return (0);
}

/*control validity of token sequence*/
int	check_token_syntax(t_token *token)
{
	t_token	*ptr;

	ptr = token;
	while (ptr)
	{
		if ((ptr->type == READ || ptr->type == WRITE || ptr->type == APPEND
				|| ptr->type == HEREDOC)
			&& (!ptr->next || ptr->next->type != WORD))
			return (0);
		else if (ptr->type == PIPE && (!ptr->next || ptr->next->type == PIPE))
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

//check return of lexer in case after this token list is empty
/*call: input division in token, check var presence and syntax*/
int	lexer(char	*input, t_data *data)
{
	int	ret;

	ret = tokenize(input, data);
	if (ret)
		return (ret);
	if (!check_token_syntax(data->token))
		return (108);
	check_shell_var(data);
	return (0);
}
