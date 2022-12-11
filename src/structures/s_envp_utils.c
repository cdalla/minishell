/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   s_envp_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/11 12:10:52 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/11 12:47:58 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_args(char **split, char *str, char c)
{
	int		w_len;

	w_len = 0;
	while(*(str +w_len) != c && *(str + w_len))
		w_len++;
	if (w_len)
		split[0] = ft_substr(str, 0, w_len);
	if (!split[0]) //malloc fail
		return (0);
	str += (w_len + 1);
	w_len = 0;
	while (*(str + w_len))
		w_len++;
	if (w_len)
	{
		split[1] = ft_substr(str, 0, w_len);
		if (!split[1]) //malloc fail
		{
			free(split[0]);
			return (0);
		}
	}
	else
		split[1] = 0;
	return (1);
}

char **split_var(char *str, char c)
{
	char	**split;

	split = (char **)malloc(3 * sizeof(char *));
	if (!split)
		return (0);
	split_args(split, str, c);
	if (!split)
	{
		free(split);
		return (0);
	}
	split[2] = 0;
	return(split);
}