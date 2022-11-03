#include "./../minishell.h"

// void    env(t_envp *envp)
// {
//     while(envp)
//     {
//         printf("%s=%s\n", envp->env, envp->value)
//         envp = envp->next;
//     }
// }

//WE CAN USE THE FUNCTION YOU WROTE ALREADY
void    env(t_envp *envp)
{
    print_env_var(envp);
}