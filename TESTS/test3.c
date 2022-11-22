#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	pid_t child;

	child = fork();
	if (child == 0)
	{
		int i = 0;
		while (i < 10)
			printf("%d\n", i++);
		printf("CHILD\n");
		exit(0);
	}
 	else if (child > 0)
	{
		//printf("PARENT\n");
		wait(NULL);
		printf("CHILD DIED");
	}
	else
		printf("ERROR\n");
	return(0);
}