/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 10:46:17 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/04 12:28:25 by cdalla-s      ########   odam.nl         */
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

/*
	create an array of words and then put every word into a token list
	or split input and put it directly into token list
*/
int tokenize(char *str, t_data *data)
{
	int		w_len;
	char	*word;

	while (*str)
	{
		w_len = 0;
		while(is_space(*str) && *str != '\0')
			str++;
		while (!is_space(str[w_len]))
			w_len++;
		word = ft_substr(str, 0, w_len);
		if (!word)
			return (0); //failure error in substr
		//here we can put a lexical checker for every word inside the previous if statement
		add_token(&data->token, word, 0); // type not recognized yet, to change or to evaluate later
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
