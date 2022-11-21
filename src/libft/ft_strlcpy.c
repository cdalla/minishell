/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:26:23 by rpicot        #+#    #+#                 */
/*   Updated: 2022/02/23 16:26:24 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	srclen_with_term_char;

	srclen_with_term_char = ft_strlen(src) + 1;
	if (dstsize >= srclen_with_term_char)
		ft_memcpy(dest, src, srclen_with_term_char);
	else if (dstsize > 0)
	{
		ft_memcpy(dest, src, dstsize - 1);
		dest[dstsize - 1] = '\0';
	}
	return (srclen_with_term_char - 1);
}
