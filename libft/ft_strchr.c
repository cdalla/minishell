/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:26:00 by rpicot        #+#    #+#                 */
/*   Updated: 2022/02/23 16:26:00 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	unsigned char	carac;
	char			*res;
	int				i;

	i = 0;
	carac = (char)c;
	while (s[i])
	{
		if (s[i] == carac)
		{
			res = (char *)(&s[i]);
			return (res);
		}
		i++;
	}
	if (s[i] == carac)
	{
		res = (char *)(&s[i]);
		return (res);
	}
	else
		return (0);
}
