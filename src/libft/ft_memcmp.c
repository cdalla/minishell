/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:25:13 by rpicot        #+#    #+#                 */
/*   Updated: 2022/02/23 16:25:14 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str_one;
	unsigned char	*str_two;
	int				i;

	i = 0;
	str_one = (unsigned char *)s1;
	str_two = (unsigned char *)s2;
	if (n)
	{
		while (str_one[i] == str_two[i] && n > 1)
		{
			i++;
			n--;
		}
		return (str_one[i] - str_two[i]);
	}
	return (0);
}
