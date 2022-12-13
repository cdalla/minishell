#include <unistd.h>
#include <sys/param.h>
#include "../src/libft/libft.h"
int main(void)
{
	char *path;

	path = getcwd(path, MAXPATHLEN);
	if (path)
		path = ft_strjoin();
	return (0);
}