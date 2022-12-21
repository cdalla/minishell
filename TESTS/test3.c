#include <sys/types.h>
#include <sys/param.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
	pid_t child;
	int fd;

	child = fork();
	if (child == 0)
	{
		int i = 0;
		while (i < 10)
			printf("%d\n", i++);
		printf("CHILD\n");
		fd = open("test_file" , O_WRONLY | O_APPEND |  O_CREAT , 0777);
		write(fd, "ciao", 4);
		close(fd);
		fd = open("test_file", O_RDONLY);
		if (fd == -1)
			printf("second open error\n");
		close(fd);
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