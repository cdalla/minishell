/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_remove.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/18 00:07:42 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/30 11:52:19 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes_counter(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

char	*trim_quotes(char *str, int quote_count)
{
	int		i;
	int		j;
	char	*new_word;
	
	i = 0;
	j = 0;
	new_word = (char *)malloc((ft_strlen(str) - quote_count + 1) * sizeof(char));
	if (!new_word)
		return (0); //malloc error
	while(str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
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
	t_token *ptr;
	char	*new_word;
	int		quote_count;

	ptr = token;
	while(ptr)
	{
		quote_count = quotes_counter(ptr->word);
		if (quote_count)
		{
			new_word = trim_quotes(ptr->word, quote_count);
			if(!new_word)
				return (107);
			free(ptr->word);
			ptr->word = new_word;
		}
		ptr = ptr->next;
	}
	return (0);
}