#include "./../minishell.h"

static void    remove_node(t_envp *envp, t_envp **head)
{
    if(!(envp->next && envp->prev))
    {
        if(envp->next)
        {
            *head = envp->next;
            (*head)->prev = NULL;
    }
    if(envp->prev)
    {
        envp->next->prev = envp->prev;
        envp->prev->next = envp->next;
    }
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
    vars = ft_split(var, ' ');
    if(!vars)
        return(0);
    head = envp;
    while(*vars)
    {
        while((*envp)->next)
        {
            if(ft_strncmp((*envp)->env, var, ft_strlen(var)) == 0)
            {
                remove_node(*envp, head);
                break ;
            }
            *envp = (*envp)->next;
        }
        *envp = *head;
        vars++;
    }
    return(1);
}
//compare it with s_envp + remove unnecessary data

/*Remove each variable or function name.
If no options are supplied, each name refers to a variable;
no variable by that name, if any, is unset. --> Readonly variables and functions may not be unset. READONLY ?
Some shell variables lose their special behavior if they are unset; such behavior is noted in the description of the individual variables. LOOKUP INDIVIDUAL VARIABLES
The return status is zero unless a name is readonly or may not be unset.*/