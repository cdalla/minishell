#include <stdio.h>

void modify_str(char *str)
{
	*str = 'a';
}

int main(void)
{
	char str[5] = "ciao";

	printf("%s\n", str);
	modify_str(str);
	printf("%s\n", str);
}