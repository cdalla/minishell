/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 10:46:17 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/15 13:32:00 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	read string input and divide into tokens
	split by spaces
*/
int	is_space(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ' || c == '\n')
		return (1);
	return (0);
}

int quote_check(int value)
{
	if (value == 0)
		return (1);
	return (0);
}

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
char	*trim_word(char **str, int *w_len)
{
	char	*word;
	int		quote;
	int		dquote;

	quote = 0;
	dquote = 0;
	while (is_space(**str) && **str != '\0')
		(*str)++;
	while (((!is_space(*(*str + *w_len))) || quote || dquote)
			&& *(*str + *w_len) != '\0')
	{
		if (*(*str + *w_len) == '\'')
			quote = quote_check(quote);
		if (*(*str + *w_len) == '\"')
			dquote = quote_check(dquote);
		(*w_len)++;
	}
	if (*w_len)
		word = ft_substr(*str, 0, *w_len);
	if (!word)
		return (0);
	return (word);
}

/*
	split input into words and put it directly into token list
*/
int tokenize(char *str, t_data *data)
{
	int		w_len;
	char	*word;

	while (*str)
	{
		w_len = 0;
		word = trim_word(&str, &w_len);
		if (!word)
			return (0); //failure error in substr
		if (!add_token(&data->token, word, 0)) // type not recognized yet, to change or to evaluate later
			return (0); //failed malloc
		str += w_len;
	}
	return (1); //success
}



/*
	call the tokenize_f
	check for lexical errors after tokenize or inside it
	LEXICAL ERRORS?????? WHAT ARE THE CASES????
*/
int	lexer (char	*input, t_data *data)
{
	tokenize(input, data);
}
