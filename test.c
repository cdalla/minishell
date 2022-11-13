#include <stdio.h>


void increase(char **str, int *value)
{
	int i = 0;
	while (i < 4)
	{
		(*str)++;
		(*value)++;
		i++;
	}
}

int main (void)
{
	char *str = "ciao mona";
	int value = 0;
	increase(&str, &value);
	printf("%s and %d\n", str, value);
	return (0);
}