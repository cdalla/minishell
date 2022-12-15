/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 16:36:22 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/15 12:32:47 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_free(char *s1, char *s2);
int	len_to_trim(char *str);
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
/*look for var_name in envp, return a copy of var->value*/
char	*expand_value(char *var, t_data *data)
{
	char	*var_name;

	var_name = ft_substr(var, 1, ft_strlen(var) - 1);
	if (!var_name)
		return (0); //malloc error //qui mettere if token type redirection and value empty dont expand
	if (!var_exist(data->envp, var_name))
		return (ft_strdup(""));
	return (ft_strdup(get_env_value(var_name, data)));
}

/*trim part from copy_str and join it with token->word, if it is var expand value*/
int	trim_join(t_token *token, t_data *data, char *str, int w_len)
{
	char	*tmp;
	char	*to_join;

	to_join = ft_substr(str, 0, w_len);
	if(!to_join)
		return (0);
	if (to_join[0] == '$')
	{
		tmp = ft_strdup(to_join);
		if (!tmp)
		{
			free(to_join);
			return (0); //malloc fail
		}
		to_join = expand_value(tmp, data);
		if (!to_join)
			return (0); //malloc fail
	}
	if (token->word)
		token->word = ft_strjoin_free(token->word, to_join);
	else
		token->word = ft_strjoin_free(ft_strdup(""), to_join);
	if (!token->word)
		return (0); //malloc fail
	return (1);
}

/*count len part to join to new str, call join_expansion function*/
int	expand_in_str(t_token *token, t_data *data) //need to expand every var in the str
{
	char	*copy;
	int		w_len;

	copy = ft_strdup(token->word);
	if (!copy)
		return (0); //malloc fail
	free(token->word);
	token->word = 0;
	while (*copy)
	{
		w_len = len_to_trim(copy);		
		if (w_len)
		{
			if (!trim_join(token, data, copy, w_len))
				return (0); //malloc fail
		}
		copy += w_len;
	}
	return (1);
}

/*check if expand in a str or only var name*/
int	expand_check(t_token *token, t_data *data)
{
	char	*new_value;
	
	if (token->word[0] == '$')
	{
		new_value = expand_value(token->word, data);
		if (!new_value)
			return (0); //malloc fail
		free(token->word);
		token->word = new_value;
	}
	else //is in a string
	{
		if (!expand_in_str(token, data))
			return (0); //malloc error
	}
	return (1);
}

//parse tokens and check if there is a var to expand
int	expander(t_data *data)
{
	t_token	*ptr;

	ptr = data->token;
	while (ptr)
	{
		if (ptr->word[0] != '\'' && ft_strchr(ptr->word, '$'))
		{
			if (!expand_check(ptr, data))
				return (0); // malloc error
		}
		ptr = ptr->next;
	}
	return (1);
}
