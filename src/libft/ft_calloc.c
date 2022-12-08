#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	index;
	char	*ptr;

	index = 0;
	ptr = (char *)malloc(count * size);
	if (ptr == 0)
		return (0);
	while (index < count * size)
	{
		ptr[index] = 0;
		index++;
	}
	return (ptr);
}
