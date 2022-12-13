/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 16:36:22 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/13 17:23:45 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	expand variables to their value
	if $var between single quotes dont expand
	loop through tokens and check value


	check token value
	if starts with single quote skip
	check if there is a $ sign
	change the value of the word with the value of the var


	redirection -> var empty -> keep the $var -> ambiguous redirect 
*/

int	expand_value(t_token *token, t_data *data)
{
	char	*var_name;
	char	*new_value;
	
	if (token->word[0] == "$")
	{
		var_name = ft_substr(token->word, 1, ft_strlen(token->word) - 1);
		if (!var_name)
			return (0); //malloc error
		free(token->word);
		token->word = ft_strdup(get_env_value(var_name, data));
	}
	else //is in a string
	{
		expand_in_str()
	}
	
}

int	expander(t_data *data)
{
	t_token	*ptr;

	ptr = data->token;
	while (ptr)
	{
		if (ptr->word[0] == '\'' || !ft_strchr(ptr->word, "$"))
			ptr = ptr->next;
		else
		{
			if (!expand_value(ptr, data))
				return (0); // malloc error
		}
		ptr = ptr->next;
	}
	return (1);
}