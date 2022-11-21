/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:26:52 by rpicot        #+#    #+#                 */
/*   Updated: 2022/02/23 16:27:09 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	find_length_to_allocate(size_t prefered_len, size_t actual_len)
{
	if (actual_len > prefered_len)
		return (prefered_len);
	else
		return (actual_len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*str;
	size_t				counter;
	size_t				slength;
	size_t				length_of_substring;

	if (!s)
		return (NULL);
	slength = ft_strlen(s);
	counter = 0;
	if (start <= slength)
	{
		length_of_substring = find_length_to_allocate(len, slength - start);
		str = (char *)malloc(sizeof(char) * (length_of_substring + 1));
		if (!str)
			return (NULL);
		while (counter < length_of_substring)
		{
			str[counter] = s[start];
			counter++;
			start++;
		}
		str[counter] = '\0';
		return (str);
	}
	return (ft_strdup(""));
}
