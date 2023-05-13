/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 16:36:22 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/05/09 16:11:36 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_to_trim(char *str, int quote, int dquote);
int	add_to_new_str(t_token *token, char *to_add);
int	expand_quotes(char **str, t_token *ptr, t_token *prev, t_data *data);

/*look for var_name in envp, return a copy of var->value*/
int	expand_var(char **var_name, t_token *prev, t_data *data)
{
	int		ret;
	char	*value;

	ret = 0;
	value = NULL;
	if (!ft_strncmp("?", *var_name, 2))
		value = ft_itoa(data->exit_code);
	else if (!ft_strncmp("", *var_name, 2))
		value = ft_strdup("$");
	else if (!var_exist(data->envp, *var_name))
	{
		if (prev && (prev->type == READ || prev->type == WRITE
				|| prev->type == APPEND))
			return (free(*var_name), 125);
		else
			value = ft_strdup("");
	}
	else
		value = ft_strdup(get_env_value(*var_name, data));
	free(*var_name);
	if (value)
		*var_name = value;
	else
		return (107);
	return (ret);
}

int	expand_dollar(char **str, t_token *ptr, t_token *prev, t_data *data)
{
	int		len;
	int		ret;
	char	*new_v;

	ret = 0;
	len = len_to_trim(*str, 0, 0);
	if (len)
	{
		new_v = ft_substr(*str, 1, len - 1);
		if (!new_v)
			return (107);
		ret = expand_var(&new_v, prev, data);
		if (ret)
			return (ret);
		ret = add_to_new_str(ptr, new_v);
		if (ret)
			return (ret);
		*str = *str + len;
	}
	else
		*str = *str + 1;
	return (ret);
}

//trim var to expand or part of str to add to new_value
int	expand_str(char *str, t_token *ptr, t_token *prev, t_data *data)
{
	int		ret;

	ret = 0;
	free(ptr->word);
	ptr->word = 0;
	while (*str && !ret)
	{
		if (*str == '$')
			ret = expand_dollar(&str, ptr, prev, data);
		else if ((*str == '\'' || *str == '\"'))
			ret = expand_quotes(&str, ptr, prev, data);
		else
		{
			ret = add_to_new_str(ptr, ft_substr(str, 0, 1));
			if (!ret)
				str = str + 1;
		}
	}
	return (ret);
}

//parse tokens and check if there is a var to expand
int	expander(t_data *data)
{
	t_token	*ptr;
	t_token	*prev;
	int		ret;
	char	*str;

	ptr = data->token;
	prev = 0;
	while (ptr)
	{
		if (ft_strchr(ptr->word, '$'))
		{
			str = ft_strdup(ptr->word);
			if (!str)
				return (107);
			ret = expand_str(str, ptr, prev, data);
			free(str);
			if (ret)
				return (ret);
		}
		prev = ptr;
		ptr = ptr->next;
	}
	return (0);
}
