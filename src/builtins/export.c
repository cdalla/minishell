#include "./../minishell.h"


//not sure in we need to include '/' '.' ':' '-' '_' in the valid characters
//A word consisting solely of letters, numbers, and underscores, and beginning with a letter or underscore.
int is_string_valid(char *str)
{
    while(*str && (*str >= 'a' && *str <= 'z') 
        || (*str >= 'A' && *str <= 'Z')
        || (*str >= '0' && *str <= '9') || *str == '_')
        str++;
    if(*str)
        return(0);
    return(1);
}

void    print_env_var(t_envp *envp)
{
    while(envp)
    {
        printf("%s", envp->env);
        if(envp->value)
            printf("%s", envp->value);
        envp = envp->next;
    }
}

void    fill_env_var(t_envp *new_node, char **str, int i)
{
    new_node->env = str[0];
    if(i == 2)
        new_node->value = str[1];
}

void	append_env(t_envp *envp, t_envp *new_node)
{
    envp->last_node->next = new_node;
    envp->last_node = new_node;
}

int    export(t_envp *envp, char *args)
{
    t_envp  *new_node;
    int     error;
    int     i;
    char    **str;

    i = 0;
    str = ft_split(args, '=');
    while(str[i])
    {
        if(!is_string_valid(str[i++]))
            return(1);//errno, invalid name
    }
    if(!str[0]) //not sure what we check here
        print_env_var(envp);
    else if(i == 1 || i == 2)
    {
        new_node = (t_envp *)malloc(sizeof(t_envp));
        if(!new_node)
            return(NULL);
        fill_env_var(&new_node, str, i);
        append_env(envp, &new_node);
    }
    return(0);
}

//do the same as unset
/*
    split =
    check_string validity
    malloc new node
    fill one if i = 1, fill 2 if i = 2
    append node

*/