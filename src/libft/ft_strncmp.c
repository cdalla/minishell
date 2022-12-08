#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	if (n == 0)
		return (0);
	while (index < n && s1[index])
	{
		if (s1[index] != s2[index])
			return ((unsigned char) s1[index] - s2[index]);
		else if (index + 1 == n)
			break ;
		else
			index++;
	}
	return ((unsigned char) s1[index] - s2[index]);
}
