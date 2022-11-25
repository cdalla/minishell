/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_free.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:26:16 by rpicot        #+#    #+#                 */
/*   Updated: 2022/11/25 22:26:05 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	strlcat_cpy(char *str, char const *s1, char const *s2)
{
	int	i;
	int	sec_i;

	sec_i = 0;
	i = 0;
	if(s1 && *s1)
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
	}
	while (s2[sec_i])
	{
		str[i] = s2[sec_i];
		i++;
		sec_i++;
	}
	str[i] = '\0';
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	int		length;
	int		length_final;

	if (!s2)
	{
        if(s1)
			return ((char *)s1);
		else
			return (NULL);
	}
	length = ft_strlen(s1);
	length_final = length + ft_strlen(s2) + 1;
	str = (char *)malloc(length_final * sizeof(char));
    strlcat_cpy(str, s1, s2);
	if (s1)
        free(s1);
    free(s2);
    if(!str)
	    return (NULL);
    return(str);
}
