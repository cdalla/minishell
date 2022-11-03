/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:25:56 by rpicot        #+#    #+#                 */
/*   Updated: 2022/02/23 16:25:57 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	exit_free(char	**s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static size_t	count_words(char	*s, char c)
{
	size_t	count;
	size_t	iteration;

	iteration = 0;
	count = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			iteration++;
			s++;
		}
		if (iteration > 0)
			count++;
		iteration = 0;
	}
	return (count);
}

static char	*skip_delim(char *s, char c)
{
	while (*s && *s == c)
		s++;
	return (s);
}

static void	count_alloc_fill(char	*s, char	**two_dim, char c)
{
	char	*original;
	int		i;

	i = 0;
	while (*s)
	{
		original = s;
		while (*s != c && *s)
			s++;
		if (s > original)
		{
			two_dim[i] = (char *)malloc(sizeof(char) * (s - original + 1));
			if (!two_dim[i])
				break ;
			ft_strlcpy(two_dim[i], original, s - original + 1);
			i++;
		}
		s = skip_delim(s, c);
	}
	two_dim[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**two_dim;
	char	*cpy_s;
	int		alloc;

	if (!s)
		return (NULL);
	cpy_s = (char *)s;
	alloc = count_words(cpy_s, c);
	two_dim = (char **)malloc(sizeof(char *) * (alloc + 1));
	if (alloc == 0)
	{
		*two_dim = NULL;
		return (two_dim);
	}
	if (!two_dim)
		return (NULL);
	count_alloc_fill(cpy_s, two_dim, c);
	if (!two_dim[0])
	{
		exit_free(two_dim);
		return (NULL);
	}
	return (two_dim);
}
