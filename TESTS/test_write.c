#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main (int argc, char **argv)
{
	int		fd;
	char	*tmp = "test_file.txt";
	char	*del;
	char	*str = NULL;

	if (argc != 2)
		return (0);
	del = strdup(argv[1]);
	if (!del)
		return (0);
	fd = open(tmp , O_WRONLY | O_APPEND |  O_CREAT , 0777);
	if (fd == -1)
	{
		printf("file not opened\n");
	}
	else
	{
		while (1)
		{
			if (str) //if read_line is something
			{
				free(str);
				str = NULL;
			}
			str = readline("gimmeheredoc>");
			if (!strcmp(del, str))
				break ;
			write(fd, str, strlen(str));
			write(fd, "\n", 1);
		}
		close(fd);
		unlink(tmp);
	}
		return (0);
}