/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 10:46:17 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/15 16:07:06 by cdalla-s      ########   odam.nl         */
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

int	is_space(int c);
int quote_check(int value);
int	type_recogn(char *word);

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
	int		type;

	while (*str)
	{
		w_len = 0;
		word = trim_word(&str, &w_len);
		if (!word)
			return (0); //failure error in substr
		type = type_recogn(word);
		if (!add_token(&data->token, word, type))
			return (0); //failed malloc
		str += w_len;
	}
	return (1); //success
}

int	lexer (char	*input, t_data *data)
{
	tokenize(input, data);
	print_tokens(data->token);
	//call to the parser
	free_tokens(data);
	return (0);
}
