/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   s_envp_values.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/25 11:40:00 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/04/29 14:40:30 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//trim var name
int	trim_arg1(char **split, char *str, char c)
{
	int		w_len;

	w_len = 0;
	while (*(str + w_len) != c && *(str + w_len))
		w_len++;
	if (w_len)
		split[0] = ft_substr(str, 0, w_len);
	if (!split[0])
		return (0);
	return (1);
}

//trim var value, if = with no value save "\0", if no = save NULL
int	trim_arg2(char **split, char *str)
{
	int		w_len;

	w_len = 0;
	while (*(str) && *(str + w_len + 1))
		w_len++;
	if (w_len)
	{
		split[1] = ft_substr(str, 1, w_len);
		if (!split[1])
			return (0);
	}
	else
	{
		if (*str == '=')
		{
			split[1] = ft_strdup("\0");
			if (!split[1])
				return (0);
		}
		else
			split[1] = 0;
	}
	return (1);
}

/*create envp args[2] for name_env and value_env*/
char	**split_var(char *str, char c)
{
	char	**split;

	split = (char **)malloc(3 * sizeof(char *));
	if (!split)
		return (NULL);
	if (!trim_arg1(split, str, c))
		return (NULL);
	else
		str += (ft_strlen(split[0]));
	if (!trim_arg2(split, str))
		return (free(split[0]), NULL);
	split[2] = 0;
	return (split);
}
