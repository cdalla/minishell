#include "./../minishell.h"

int unset(t_envp **head, char *var)
{
    char    **vars;
    t_envp  *envp;

    vars = ft_split(var, ' ');
    if(!vars)
        return(0);
    envp = *head;
    while(*vars)
    {
        if(is_str_valid(*vars))
        {
            while(envp)
            {
                if(ft_strcmp(envp->env, var) == 0)
                {
                    remove_envp(head, envp);
                    break ;
                }
                envp = envp->next;
            }
        }
        envp = *head;
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