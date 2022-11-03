#include "./../minishell.h"

int    echo(char *options, char *str)
{
    int status;

    status = printf(str);
    if(status != -1 && ft_strcmp(*options, "\n") != 0)
        status = write(1, "\n", 1);
    if(status == -1)
        return (-1);
    return (0);
}