#include "./../minishell.h"

int pwd(t_envp *envp)
{
    char    *buff;
    int errno;
    buff = get_envp(envp, "PWD");
    if((errno = printf("%s", buff)) == -1)
        return(-1);
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

envp-> *envp -> **envp
*/