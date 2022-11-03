/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:24:32 by rpicot        #+#    #+#                 */
/*   Updated: 2022/02/25 13:59:31 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	bytes_to_allocate(int n)
{
	int	bytes;

	bytes = 0;
	if (n <= 0)
		bytes++;
	while (n)
	{
		n /= 10;
		bytes++;
	}
	bytes++;
	return (bytes);
}

static char	*cast_int_to_char(int bytes_fill, long num_to_convert, char *dest)
{
	int	check;

	check = 1;
	bytes_fill--;
	dest[bytes_fill] = '\0';
	bytes_fill--;
	if (num_to_convert < 0)
	{
		check = -1;
		dest[0] = '-';
		num_to_convert *= -1;
	}
	while (bytes_fill > 0)
	{
		dest[bytes_fill] = num_to_convert % 10 + '0';
		num_to_convert = num_to_convert / 10;
		bytes_fill--;
	}
	if (check > 0)
		dest[bytes_fill] = num_to_convert % 10 + '0';
	return (dest);
}

char	*ft_itoa(int n)
{
	int		bytes;
	int		test;
	char	*res;

	test = n;
	bytes = bytes_to_allocate(test);
	res = malloc(sizeof(char) * bytes);
	if (!res)
		return (NULL);
	res = cast_int_to_char(bytes, test, res);
	return (res);
}
