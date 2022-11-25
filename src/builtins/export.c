#include "./../minishell.h"

int    export(t_envp **envp, char *args)
{
    int     error;
    int     i;
    char    **str;

    i = 0;
    str = ft_split(args, ' ');
    if(!str)
        return(1);
    else if(!*str)
        read_envp(*envp);
    while(str[i])
    {
        error = format_and_add(envp, str[i]);
        if(error == -1)
            break;
        i++;
    }
    return(0);
}
