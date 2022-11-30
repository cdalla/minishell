#include <stdio.h>

int main(void)
{
	int i = 0;
	while (i < 10)
	{
		printf("%d\n   %d", i % 2, i / 2);
		i++;
	}
	return (0);
}