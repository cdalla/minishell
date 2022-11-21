/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:26:48 by rpicot        #+#    #+#                 */
/*   Updated: 2022/02/23 16:26:49 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	left_limit(const char *set, const char *s1, int i)
{
	while (ft_strchr(set, s1[i]) && s1[i])
		i++;
	return (i);
}

static int	right_limit(const char *set, const char *s1, int len)
{
	while (ft_strchr(set, s1[len]))
	{
		if (!(len > 0))
			break ;
		len--;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	if (!s1 || !set)
		return (ft_strdup(""));
	len = (int)ft_strlen(s1) - 1;
	i = left_limit(set, s1, i);
	len = right_limit(set, s1, len);
	if (len < i)
		return (ft_strdup(""));
	if (i == 0 && (int)ft_strlen(s1) == len + 1)
		return (ft_strdup(s1));
	res = (char *)malloc(sizeof(char) * ((len - i) + 2));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1 + i, (len - i) + 2);
	return (res);
}
