/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_quoted.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 15:10:17 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/05/09 15:37:25 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_to_trim(char *str, int quote, int dquote);
int	add_to_new_str(t_token *token, char *to_add);
int	expand_dollar(char **str, t_token *ptr, t_token *prev, t_data *data);

int	expand_dquoted_str(char **str, t_token *ptr, t_token *prev, t_data *data)
{
	char	*q_str;
	char	*str_ptr;
	int		ret;
	int		len;

	len = len_to_trim(*str, 0, 1);
	q_str = ft_substr(*str, 1, len);
	if (!q_str)
		return (107);
	str_ptr = q_str;
	while (*q_str)
	{
		if (*q_str == '$')
			ret = expand_dollar(&q_str, ptr, prev, data);
		else
		{
			ret = add_to_new_str(ptr, ft_substr(q_str, 0, 1));
			if (!ret)
				q_str = q_str + 1;
		}
		if (ret)
			return (free(str_ptr), ret);
	}
	free(str_ptr);
	return (ret);
}

int	expand_double_quotes(char **str, t_token *ptr, t_token *prev, t_data *data)
{
	int	ret;
	int	len;

	ret = add_to_new_str(ptr, ft_strdup("\""));
	if (ret)
		return (ret);
	len = len_to_trim(*str, 0, 1);
	if (len)
	{
		ret = expand_dquoted_str(str, ptr, prev, data);
		if (ret)
			return (ret);
	}
	ret = add_to_new_str(ptr, ft_strdup("\""));
	if (ret)
		return (ret);
	*str = *str + len + 2;
	return (ret);
}

int	expand_quotes(char **str, t_token *ptr, t_token *prev, t_data *data)
{
	int	len;
	int	ret;

	ret = 0;
	if (**str == '\'')
	{
		len = len_to_trim(*str, 1, 0);
		ret = add_to_new_str(ptr, ft_substr(*str, 0, len));
		if (ret)
			return (ret);
		*str = *str + len;
	}
	else if (**str == '\"')
		ret = expand_double_quotes(str, ptr, prev, data);
	return (ret);
}
