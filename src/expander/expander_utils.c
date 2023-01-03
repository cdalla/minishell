/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/15 12:06:05 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/03 15:46:05 by cdalla-s      ########   odam.nl         */
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
		return (0);
	ft_strlcpy(&(join[ft_strlcpy(join, s1, len)]), s2, len);
	free(s1);
	free(s2);
	return (join);
}

/*count var_name len or part to join len*/
int	len_to_trim(char *str)
{
	int	w_len;

	w_len = 0;
	if (*str == '$')
	{
		w_len++;
		while (ft_isalpha(*(str + w_len)) || ft_isdigit(*(str + w_len)
				&& *(str + w_len)) || *(str + w_len) == '_')
			w_len++;
	}
	else
	{
		while (*(str + w_len) != '$' && *(str + w_len))
			w_len++;
	}
	return (w_len);
}
