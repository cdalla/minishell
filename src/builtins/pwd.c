#include "./../minishell.h"
#include <limits.h>

int pwd()
{
    char *path;
    int     errno;

    path  = getcwd(path, PATH_MAX);
	//read it from the linked list
    if (path = NULL)
        return(errno);
    printf("%s", path);
    return(0);
}

/*
    pwd ¶
    pwd [-LP]
    Print the absolute pathname of the current working directory. 
    If the -P option is supplied, the pathname printed will not contain symbolic links.
    If the -L option is supplied, the pathname printed may contain symbolic links.
    The return status is zero unless an error is encountered while determining the
    name of the current directory or an invalid option is supplied.
*/