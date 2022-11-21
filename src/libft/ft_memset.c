/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:25:37 by rpicot        #+#    #+#                 */
/*   Updated: 2022/02/23 16:25:38 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memset(void *dest, int c, size_t len)
{
	unsigned char	*mem;
	int				i;

	mem = (unsigned char *)dest;
	i = 0;
	while (len > 0)
	{
		mem[i] = c;
		i++;
		len--;
	}
	return (dest);
}
