/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/15 12:06:05 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/05/06 15:05:06 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	multi_var(char *str)
// {
// 	int	i;
// 	int	count;

// 	count = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 			count++;
// 		i++;
// 	}
// 	if (count > 1)
// 		return (1);
// 	return (0);
// }

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
		return (0);
	ft_strlcpy(&(join[ft_strlcpy(join, s1, len)]), s2, len);
	free(s1);
	free(s2);
	return (join);
}

/*count var_name len or part to join len*/
// int	len_to_trim(char *str)
// {
// 	int	w_len;
// 	int	quote;

// 	w_len = 0;
// 	quote = 0;
// 	if (*str == '$' && (*(str + 1) == '?' || ft_isdigit(*(str + 1))))
// 		w_len = 2;
// 	else if (*str == '$')
// 	{
// 		w_len++;
// 		while (ft_isalpha(*(str + w_len)) || ft_isdigit(*(str + w_len))
// 			|| *(str + w_len) == '_')
// 			w_len++;
// 	}
// 	else
// 	{
// 		while (*(str + w_len) && (*(str + w_len) != '$' || quote))
// 		{
// 			if (*(str + w_len) == '\'')
// 				quote_check(&quote, NULL, '\'');
// 			w_len++;
// 		}
// 	}
// 	return (w_len);
// }


int	valid_name(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}

/*count var_name len or part to join len*/
int	len_to_trim(char *str)
{
	int	w_len;
	int	quote;
	int	d_quote;

	w_len = 0;
	quote = 0;
	d_quote = 0;
	if (*str == '$')
	{
		// if ((*(str + 1) == '\'') || (*(str + 1) == '\"'))
		// 	return (0);
		w_len++;
		if ((*(str + 1) == '?' || ft_isdigit(*(str + 1))))
			return (2);
		while (*(str + w_len) && valid_name(*(str + w_len)))
				w_len++;
	}
	else
	{
		while (*(str + w_len) && (*(str + w_len) != '$' || quote))
		{
			if (*(str + w_len) == '\'' || *(str + w_len) == '\"')
				quote_check(&quote, &d_quote, *(str + w_len));
			w_len++;
		}
	}
	return (w_len);
}


/*
!(w_len == 1 && *copy == '$' && ((*(copy + 1) == '\'') || *(copy + 1) == '\"')))
*/