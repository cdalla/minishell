#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "./test.h"

void    remove_node(t_envp *envp, t_envp **head)
{
    if(!(*envp->next && *envp->prev))
    {
        if(envp->next)
            *head = envp->next;
    }
    envp->next->prev = envp->prev;
    envp->prev->next = envp->next;
    free(envp->env);
    if(!envp->value)
        free(envp->value);
    free(envp);
    
}

int unset(t_envp **envp, char *var)
{
    int     errno;
    char    **vars;
    t_envp  **head;

    errno = 0;
    vars = ft_split(var);
    if(!vars)
        return(0);
    head = envp;
    while(*vars)
    {
        while((*envp)->next)
        {
            if(ft_strcmp((*envp)->env, var) == 0)
            {
                remove_node(*envp, head);
                break ;
            }
            envp = (*envp)->next;
        }
        envp = head;
        vars++;
    }
    return(1);
}