/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 10:46:17 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/11 17:39:29 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	read string input and divide into tokens
	split by spaces
*/
/*
	move the str pointer further until beginning of word to trim
	assign to w_len the correct lenght of the word
	split words on spaces
	unless quote or double quote is open

	examples:

	cat -e hello -> 3 tokens
	cat -e "hello chico" -> 3 tokens
	echo "ciao"Rafa"nice covid" -> 2 tokens
*/

char	*trim_word(char **s, int *wl)
{
	char	*word;
	int		quote;
	int		dquote;

	word = 0;
	quote = 0;
	dquote = 0;
	while (((!is_space(*(*s + *wl))) || quote || dquote) //if it is not a space or quotes are opened
		&& *(*s + *wl) != '\0')
	{
		if (*(*s + *wl) == '\'' || *(*s + *wl) == '\"')
			quote_check(&quote, &dquote, *(*s + *wl));
		// if ((*(*s + *wl) == '>' || *(*s + *wl) == '<' || (*(*s + *wl) == '$'
		// 	&& *(*s + *wl + 1) == '?')) && !quote && !dquote) //if this one is redirection trim symbol
		if ((is_redirection((*s + *wl)) && !quote && !dquote))
		{
			(*wl) += is_redirection((*s + *wl));
			break ;
		}
		(*wl)++;
		if (is_redirection((*s + *wl)) && (!quote && !dquote)) //if next is redirection break
			break ;
	}
	if (*wl)
		word = ft_substr(*s, 0, *wl);
	return (word);
}

/*
	split input into words and put it directly into token list
*/
int	tokenize(char *str, t_data *data)
{
	int		w_len;
	char	*word;
	int		type;

	while (*str)
	{
		w_len = 0;
		while (is_space(*str) && *str) //skip all spaces
			str++;
		if (ft_strlen(str))
		{
			word = trim_word(&str, &w_len);
			if (!word)
				return (0); //failure error in substr
			type = type_recogn(word);
			if (!add_token(&data->token, word, type))
				return (0); //failed malloc
			str += w_len;
		}
	}
	return (1); //success
}


int	check_token_syntax(t_token *token)
{
	t_token	*ptr;

	ptr = token;
	while (ptr)
	{
		if ((ptr->type == REDI || ptr->type == REDO || ptr->type == REDOA
				|| ptr->type == HEREDOC) && ptr->next->type != WORD)
		{
			printf("syntax error\n");
			return (0);
		}
		else if (ptr->type == PIPE && (!ptr->next || ptr->next->type == PIPE ))
		{
			printf("syntax error\n");
			return (0);
		}
		ptr = ptr->next;
	}
	return (1);
}

//check return of lexer in case after this token list is empty
int	lexer(char	*input, t_data *data)
{
	if (!tokenize(input, data))
		return (0);
	print_tokens(data->token);//to be removed
	check_shell_var(data);
	if (!check_token_syntax(data->token))
		return (0);
	return (1);
}
