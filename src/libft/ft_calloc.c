/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:24:05 by rpicot        #+#    #+#                 */
/*   Updated: 2022/02/23 16:24:07 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*memory;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	memory = (unsigned char *)malloc(size * count);
	if (!memory)
		return (NULL);
	ft_bzero(memory, count * size);
	return (memory);
}
