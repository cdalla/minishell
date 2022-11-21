/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   s_envp.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 10:55:25 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/21 12:11:08 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	pointer to the s_envp list in main struct
	create a new node, check for valid input
	add a new node to envp list, used to initialize it and add variables later
	we can add an extra variable to set if the env is printable or not
*/

//not sure in we need to include '/' '.' ':' '-' '_' in the valid characters
//NEED TO FIX THIS
//IT IS WORKING BUT WE NEED TO INCLUDE ALL THE CHARACTERS POSSIBLE
int is_str_valid(char *str)
{
	(void)str;
    // while(*str && ((*str >= 'a' && *str <= 'z')
    //     || (*str >= 'A' && *str <= 'Z')
    //     || (*str >= '0' && *str <= '9')))
    //     str++;
    // if(*str)
    //     return(0);
    return(1);
}

t_envp	*new_envp(char *arg)
{
	t_envp	*new_node;
	char	**args;

	new_node = (t_envp *)malloc(sizeof(t_envp));
	args = ft_split(arg, '=');
	if (!new_node || !args)
		return (0); //failure
	if (!is_str_valid(args[0]) || !is_str_valid(args[1]))
		return (0);	//print_env_var(); (i guess here return with error)
	new_node->env = args[0];
	new_node->value = args[1];
	new_node->next = 0;
	new_node->prev = 0; //if we need prev
	return (new_node);
}

int	add_env(t_envp **envp, char *args)
{
	t_envp	*new;
	t_envp	*ptr;

	new = new_envp(args);
	if (!new)
		return (0); //failure
	if (!*envp) //if envp list empty
		*envp = new;
	else
	{
		ptr = *envp;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
		new->prev = ptr; //if we need previous
	}
	return (1); //success
}

void    print_env_var(t_envp *envp) //print only one var or more? 
{
	t_envp	*ptr;

	ptr = envp;
    while(ptr)
    {
    	printf("%s=%s\n", ptr->env, ptr->value);
        ptr = ptr->next;
    }
}

//remove a node from the list
int	remove_envp(t_envp **envp, t_envp *to_rem)
{
	//t_envp	*ptr;

	if (!to_rem->prev && to_rem->next) //if to_rem is first node
	{
		to_rem->next->prev = 0;
		*envp = to_rem->next;
	}
	else if (to_rem->prev && !to_rem->next) //if to_rem last node
		to_rem->prev->next = 0;
	else if (to_rem->prev && to_rem->next)
	{
		to_rem->next->prev = to_rem->prev; //next connected to prev
		to_rem->prev->next = to_rem->next; //prev connected to next
	}
	free(to_rem->env);
	free(to_rem->value);
	free(to_rem);
	return (1); //success
}
