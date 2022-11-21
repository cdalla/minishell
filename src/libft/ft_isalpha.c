/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:24:16 by rpicot        #+#    #+#                 */
/*   Updated: 2022/02/25 14:00:17 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static	int	ft_isupper(int c)
{
	if (c < 65 || c > 90)
		return (0);
	else
		return (1);
}

static	int	ft_islower(int c)
{
	if (c < 97 || c > 122)
		return (0);
	else
		return (1);
}

int	ft_isalpha(int c)
{
	if (ft_islower(c) || ft_isupper(c))
		return (c);
	else
		return (0);
}
