/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:25:48 by rpicot        #+#    #+#                 */
/*   Updated: 2022/02/23 16:25:49 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static void	split_num(long n, int fd)
{
	char	number;

	if (n >= 10)
		split_num(n / 10, fd);
	number = n % 10 + '0';
	ft_putchar_fd(number, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	num;

	num = n;
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		num *= -1;
	}
	split_num(num, fd);
}
