#include "./../minishell.h"

void    env(t_envp *envp)
{
    while(envp)
    {
        printf("%s=%s\n", envp->env, envp->value)
        envp = envp->next;
    }
}