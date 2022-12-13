#include "../src/libft/libft.h"
#include <stdio.h>

int main(void)
{
	char	*name = "$var";
	char	*sub;

	sub = ft_substr(name, 1, ft_strlen(name) - 1);
	printf("%s\n", sub);
	return (0);
}