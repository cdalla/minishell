/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/15 12:06:05 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/05/09 16:08:40 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*ft_strjoin version with free of the 2 strings used as input*/
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*join;
	size_t	len;

	if (!s1 || !s2)
		return (0);
	len = (ft_strlen((char *)s1)) + (ft_strlen((char *)s2)) + 1;
	join = (char *)malloc(len * sizeof(char));
	if (join == 0)
		return (free(s1), free(s2), NULL);
	ft_strlcpy(&(join[ft_strlcpy(join, s1, len)]), s2, len);
	free(s1);
	free(s2);
	return (join);
}

int	valid_name(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}

/*count var_name len or str in quotes*/
int	len_to_trim(char *str, int quote, int dquote)
{
	int	len;

	len = 0;
	if (dquote)
	{
		while (*(str + len + 1) && *(str + len + 1) != '\"')
			len++;
	}
	else if (quote)
	{
		while (*(str + len + 1) && *(str + len + 1) != '\'')
			len++;
		len += 2;
	}
	else if (*str == '$')
	{
		len++;
		if ((*(str + 1) == '?' || ft_isdigit(*(str + 1))))
			return (2);
		else if ((*(str + 1) == '\'' || *(str + 1) == '\"') && !dquote)
			return (0);
		while (*(str + len) && valid_name(*(str + len)))
				len++;
	}
	return (len);
}

int	add_to_new_str(t_token *token, char *to_add)
{
	if (!to_add)
		return (107);
	if (token->word)
		token->word = ft_strjoin_free(token->word, to_add);
	else
		token->word = ft_strjoin_free(ft_strdup(""), to_add);
	if (!token->word)
		return (107);
	return (0);
}
