/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:25:53 by rpicot        #+#    #+#                 */
/*   Updated: 2022/02/23 16:25:54 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	if (fd && s)
	{
		while (*s)
		{
			write(fd, s, 1);
			s++;
		}
	}
}
