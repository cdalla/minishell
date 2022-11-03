#include "./../minishell.h"

// static void unset_tester(t_envp *envp)
// {
//     t_envp *head;

//     head = envp;
//     while(envp)
//     {
//         unset(&head, envp->env);
//         envp = envp->next;
//     }
// }

static void set_env_array(char **env_array, char **env_values)
{
    env_array[0] = "test";
    env_array[1] = "";
    env_array[2] = "test2";
    env_array[3] = "test3";
    env_array[4] = "test4";
    env_array[5] = "test5";
    env_array[6] = "test6";
    env_array[7] = "test7";
    env_array[8] = "test8";
    env_array[9] = "test9";
    env_array[10] = 0;
    
    env_values[0] = "1";
    env_values[1] = "";
    env_values[2] = "test2";
    env_values[3] = "test3";
    env_values[4] = "test4";
    env_values[5] = "test5";
    env_values[6] = "test6";
    env_values[7] = "test7";
    env_values[8] = "test8";
    env_values[9] = "test9";
    env_values[10] = 0;
}
static t_envp *set_env_var(char **env_names, char **env_values)
{
    t_envp  *head;
    t_envp  *envp;
    int count = 10;
    int i = 0;
    envp = malloc(sizeof(t_envp));
    if(!envp)
        return(0);
    head = envp;
    while(count)
    {
        envp->env = env_names[i];
        envp->value = env_values[i];
        t_envp  *node;
        node = malloc(sizeof(t_envp));
        if(!node)
            return(0);
        envp->next = node;
        envp = envp->next;
        count--;
        i++;
    }
    return(head);
}

int main()
{
    char    *env_names[11];
    char    *env_values[11];
    t_envp  *head;

    set_env_array(env_names, env_values);
    head = set_env_var(env_names, env_values);
    //unset_tester(head);
}