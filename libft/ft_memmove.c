/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:25:32 by rpicot        #+#    #+#                 */
/*   Updated: 2022/02/23 16:25:34 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*source;
	unsigned char	*dest;
	int				i;

	i = 0;
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	else if (dest == source)
		return (dst);
	else if (dest < source)
		ft_memcpy(dst, src, len);
	else
	{
		while (len)
		{
			dest[len - 1] = source[len - 1];
			len--;
		}
	}
	return (dst);
}
