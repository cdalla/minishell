#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	index;
	size_t	dst_len;
	size_t	tot_len;

	index = 0;
	dst_len = ft_strlen(dst);
	tot_len = dst_len + ft_strlen((char *)src);
	if (dstsize <= dst_len)
		return ((size_t)ft_strlen((char *)src) + dstsize);
	if (dstsize > 0)
	{
		while (src[index] && dst_len + index < dstsize - 1)
		{
			dst[dst_len + index] = src[index];
			index++;
		}
		dst[dst_len + index] = '\0';
	}
	return (tot_len);
}
