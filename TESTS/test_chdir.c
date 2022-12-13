#include <unistd.h>
#include <sys/param.h>
#include "../src/libft/libft.h"
#include <stdio.h>

int main(void)
{
	char 	*path = 0;
	char	*tmp = 0;

	path = getcwd(path, MAXPATHLEN);
	if (path)
	{
		printf("%s\n", path);
		// tmp = ft_strjoin(path, "/src");
		// printf("%s\n", tmp);
		if (chdir("..") == -1)
			printf("error\n");
		free(path);
		path = getcwd(path, MAXPATHLEN);
		if (path)
			printf("%s\n", path);
	}
	return (0);
}