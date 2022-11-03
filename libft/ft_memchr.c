/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:25:09 by rpicot        #+#    #+#                 */
/*   Updated: 2022/02/25 13:59:46 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char		*str;
	unsigned char			letter;

	str = (unsigned char *)s;
	letter = c;
	while (n > 0)
	{
		if (letter == *str)
			return ((void *)str);
		n--;
		str++;
	}
	return (NULL);
}
