/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:26:26 by rpicot        #+#    #+#                 */
/*   Updated: 2022/11/25 14:47:54 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(const char *s)
{
	char	*str;

	if (!s)
		return (0);
	str = (char *)s;
	while (*s)
		s++;
	return (s - str);
}
