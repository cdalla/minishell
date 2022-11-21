/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:26:43 by rpicot        #+#    #+#                 */
/*   Updated: 2022/02/23 16:26:44 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	carac;
	char			*res;
	int				i;

	i = ft_strlen(s);
	carac = (char)c;
	while (i >= 0)
	{
		if (s[i] == carac)
		{
			res = (char *)(&s[i]);
			return (res);
		}
		i--;
	}
	return (0);
}
