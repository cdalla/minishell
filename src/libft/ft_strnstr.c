#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	index;
	size_t	n_len;
	size_t	jndex;

	index = 0;
	n_len = 0;
	while (needle[n_len])
		n_len++;
	if (n_len == 0)
		return ((char *)haystack);
	while (index < len && haystack[index])
	{
		if (haystack[index] == needle[0])
		{
			jndex = 0;
			while (jndex < n_len && haystack[index + jndex]
				== needle[jndex] && index + jndex < len)
				jndex++;
			if (jndex == n_len)
				return ((char *)haystack + index);
		}
		index++;
	}
	return (0);
}
