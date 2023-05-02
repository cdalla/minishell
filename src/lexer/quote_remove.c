/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_remove.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/18 00:07:42 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/04/28 12:01:07 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	check_quote_type(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (str[i]);
		i++;
	}
	return (0);
}

int	quotes_counter(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	*trim_quotes(char *str, int quote_count, char quote)
{
	int		i;
	int		j;
	char	*new_word;

	i = 0;
	j = 0;
	new_word = (char *)malloc((ft_strlen(str)
				- quote_count + 1) * sizeof(char));
	if (!new_word)
		return (0);
	while (str[i])
	{
		if (str[i] != quote)
		{
			new_word[j] = str[i];
			j++;
		}
		i++;
	}
	new_word[j] = '\0';
	return (new_word);
}

int	quote_removal(t_token *token)
{
	t_token	*ptr;
	char	*new_word;
	char	quote;
	int		quote_count;

	ptr = token;
	while (ptr)
	{
		quote = check_quote_type(ptr->word);
		if (quote)
		{
			quote_count = quotes_counter(ptr->word, quote);
			if (quote_count)
			{
				new_word = trim_quotes(ptr->word, quote_count, quote);
				if (!new_word)
					return (107);
				free(ptr->word);
				ptr->word = new_word;
			}
		}
		ptr = ptr->next;
	}
	return (0);
}
