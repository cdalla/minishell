/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:26:37 by rpicot        #+#    #+#                 */
/*   Updated: 2022/02/23 16:26:37 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		j;
	size_t	neelen;

	i = 0;
	j = 0;
	if (needle[0])
	{
		while (haystack[i] && len)
		{
			neelen = len;
			while (needle[j] == haystack[i + j] && neelen)
			{
				neelen--;
				if (needle[j + 1] == '\0')
					return ((char *)&haystack[i]);
				j++;
			}
			len--;
			j = 0;
			i++;
		}
		return (NULL);
	}
	return ((char *)haystack);
}
