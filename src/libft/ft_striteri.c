#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	iter;

	iter = 0;
	if (s)
	{
		while (s[iter])
		{
			f(iter, &(s[iter]));
			iter++;
		}
	}
}
