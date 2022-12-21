#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	int i = 0;
	while(i < 129)
	{
		printf("errno %d = %s\n", i, strerror(i));
		i++;
	}
	return(0);
}