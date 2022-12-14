/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 16:36:22 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/14 13:59:12 by cdalla-s      ########   odam.nl         */
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

	var_name = ft_substr(token->word, 1, ft_strlen(token->word) - 1);
	if (!var_name)
		return (0); //malloc error
	free(token->word);//qui mettere if token type redirection and value empty dont expand
	token->word = ft_strdup(get_env_value(var_name, data));
	return (1);
}

int	copy_var_str(t_data *data, t_token *token, int *w_len, char *copy)
{
	w_len = 0;
	while (!ft_isalpha(*(copy + *w_len)) && !ft_isdigit(*(copy + *w_len)
	&& *(copy + *w_len)) && *(copy + *w_len) != '_') //get var_name len, with var_name costraints
		w_len++;
	if (w_len > 1)//if 1 only $ is found, if > 1 expand
	{
		free(token->word);
		token->word = ft_substr(copy, 0, w_len);
		if (!token->word)
			return (0); //malloc failed
		if (!expand_value(token, data))
			return (0); //malloc fail i need to free something
	}
	//i need to add here only the $ to str, recalling the same function with size 1
}

int	copy_str_part(char *copy, char **str, int w_len)
{
	if (!*str && w_len) //if something before $ save it in str if first time
	{
		*str = ft_substr(copy, 0, w_len);
		if (!*str)
			return (0); //malloc fail
	}
	else if (w_len)	//if something before $ and str is something save it in tmp
	{
		tmp = ft_strjoin(str, ft_substr(copy, 0, w_len));//need to free str after probably
		if (!tmp)
			return (0); //malloc failed
	}
}

void	free_strs(char *tmp, char *str)
{
	if (tmp)
	{
		free(str);
		str = ft_strdup(tmp);
		free(tmp);
		tmp = 0;
	}
}

int	expand_in_str(t_token *token, t_data *data) //need to expand every var in the str
{
	char	*str;
	char	*var;
	char	*new_str;
	char	*copy;
	char	*tmp;
	int		w_len;
	int		i;

	copy = ft_strdup(token->word);
	if (!copy)
		return (0); //malloc fail
	while (*copy)
	{
		while(*(copy + w_len) != '$' && *(copy + w_len))//skip until $
			w_len++;
		if (!copy_str_part())
			retunr (0); //malloc failed
		copy += w_len; //here i got the part before $, increase pointer until $
		if (*copy == '$')//trim the var name, expand, join it with new str (not really needed as i know there is a $)
		{
			if (!copy_var_str(str))
				return (0); //malloc failed -- need to free
			copy += w_len;
		}
	}
	return (1);
}

int	expand_check(t_token *token, t_data *data)
{
	char	*new_value;
	
	if (token->word[0] == "$")
	{
		if (!expand_value(token, data))
			return (0); //malloc fail
	}
	else //is in a string
	{
		if (!expand_in_str(token, data))
			return (0); //malloc error
	}
	return (1);
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