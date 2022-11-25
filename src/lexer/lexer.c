/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 10:46:17 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/25 13:53:59 by cdalla-s      ########   odam.nl         */
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
int	type_recogn(char *word);
void quote_check(int *quote, int *dquote, int c);
int	is_redirection(char *c);

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
		ptr = ptr->next;
	}
	return (1);
}

char	*trim_word(char **str, int *w_len)
{
	char	*word = 0;
	int		quote;
	int		dquote;

	quote = 0;
	dquote = 0;
	while (is_space(**str) && **str != '\0') //skip all spaces
		(*str)++;
	while (((!is_space(*(*str + *w_len))) || quote || dquote) //if it is not a space or quotes are opened
			&& *(*str + *w_len) != '\0')
	{
		if (*(*str + *w_len) == '\'' || *(*str + *w_len) == '\"')
			quote_check(&quote, &dquote, *(*str + *w_len));
		if ((*(*str + *w_len) == '>' || *(*str + *w_len) == '<') && !quote && !dquote)
		{
			(*w_len) += is_redirection((*str + *w_len));
			break ;
		}
		(*w_len)++;
		if (is_redirection((*str + *w_len)) && !quote && !dquote)
			break ;
	}
	if (*w_len)
		word = ft_substr(*str, 0, *w_len);
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
	if (!tokenize(input, data))
		return (0);
	//print_tokens(data->token);
	if (!check_token_syntax(data->token))
		return (0);
	//call to the parser
	//parser(data);
	//free_tokens(data);
	printf("finished parser\n");
	return (1);
}
