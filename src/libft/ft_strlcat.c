/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:26:19 by rpicot        #+#    #+#                 */
/*   Updated: 2022/02/23 16:26:20 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	remaining_dstlen_with_termchar;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	remaining_dstlen_with_termchar = dstsize - dstlen;
	if (dstlen < dstsize)
		ft_strlcpy(dst + dstlen, src, remaining_dstlen_with_termchar);
	else if (dstlen >= dstsize)
		return (dstsize + srclen);
	return (dstlen + srclen);
}
