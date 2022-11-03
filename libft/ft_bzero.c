/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:23:57 by rpicot        #+#    #+#                 */
/*   Updated: 2022/02/23 16:24:00 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*res;

	res = (unsigned char *)s;
	while (n)
	{
		*res = '\0';
		res++;
		n--;
	}
}
