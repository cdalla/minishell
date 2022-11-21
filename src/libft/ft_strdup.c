/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:26:07 by rpicot        #+#    #+#                 */
/*   Updated: 2022/02/23 16:26:08 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		len;

	len = ft_strlen(s1) + 1;
	str = (char *)malloc(len * sizeof(char));
	if (str)
	{
		ft_strlcpy(str, s1, len);
		return (str);
	}
	return (NULL);
}
