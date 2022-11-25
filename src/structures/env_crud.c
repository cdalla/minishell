
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_crud.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 10:55:25 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/25 15:00:58 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	pointer to the s_envp list in main struct
	create a new node, check for valid input
	add a new node to envp list, used to initialize it and add variables later
*/
//not sure in we need to include '/' '.' ':' '-' '_' in the valid characters

char *get_envp(t_envp *envp, char *env)
{
    while(envp)
    {
        if(ft_strcmp(envp->env, env) == 0)
            return(envp->value);
        envp = envp->next;
    }
    printf("didn't find %s\n", env);
    return (NULL);
}

int create_envp(char **args, t_envp **envp, bool standalone)
{
	t_envp *ptr;
	t_envp *new_node;

	if(!is_str_valid(args[0])) 
		return(0);
	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (!new_node || !args)
		return (-1); //failure
	new_node->env = args[0];
	new_node->value = args[1];
	new_node->next = 0;
	new_node->prev = 0; //if we need prev
	new_node->standalone = standalone; //if we need prev
	if (!*envp) //if envp list empty
		*envp = new_node;
	else
	{
		ptr = *envp;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_node;
		new_node->prev = ptr; //if we need previous
	}
	return (1);
}

int update_envp(t_envp *envp, char **args, bool standalone)
{
	while (envp)
	{
		if (ft_strcmp(envp->env, args[0]) == 0)
		{
			if(!is_str_valid(args[0]))
				return (0);
			if(standalone)
			return(-2);
			envp->env = args[0];
			envp->value = args[1];
			envp->standalone = standalone;
			return (1);
		}
		envp = envp->next;
	}
	return(0);
}

void    read_envp(t_envp *envp) //print only one var or more? 
{
	t_envp	*ptr;

	ptr = envp;
    while(ptr)
    {
    	printf("declare -x %s", ptr->env);
		if(ptr->standalone == false)
		{
			printf("=\"");
			if(ptr->value)
    			printf("%s", ptr->value);
			printf("\"");
		}
		printf("\n");
        ptr = ptr->next;
    }
}

//remove a node from the list
int	remove_envp(t_envp **envp, t_envp *to_rem)
{
	if (!to_rem->prev && to_rem->next) //if to_rem is first node
	{
		to_rem->next->prev = NULL;
		*envp = to_rem->next;
	}
	else if (to_rem->prev && !to_rem->next) //if to_rem last node
		to_rem->prev->next = NULL;
	else if (to_rem->prev && to_rem->next)
	{
		to_rem->next->prev = to_rem->prev; //next connected to prev
		to_rem->prev->next = to_rem->next; //prev connected to next
	}
	else
		*envp = NULL;
	free(to_rem->env);
	free(to_rem);
	return (1); //success
}
