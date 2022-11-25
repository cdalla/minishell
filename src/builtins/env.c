#include "./../minishell.h"

int    env(t_envp *envp)
{
    int status;

    status = 0;
    while(envp)
    {
        if(!envp->standalone)
            status = printf("%s=%s\n", envp->env, envp->value);
        if(status == -1)
            return(-1);
        envp = envp->next;
    }
    return(0);
}
