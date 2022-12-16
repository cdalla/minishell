/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   s_envp.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 10:55:25 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/16 13:23:06 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
char **split_var(char *str, char c);
/*
	pointer to the s_envp list in main struct
	create a new node, check for valid input
	add a new node to envp list, used to initialize it and add variables later
	we can add an extra variable to set if the env is printable or not
*/

//not sure in we need to include '/' '.' ':' '-' '_' in the valid characters
//NEED TO FIX THIS
//IT IS WORKING BUT WE NEED TO INCLUDE ALL THE CHARACTERS POSSIBLE

/*check var_name correct syntax*/
int	check_var_syntax(char *str)
{
	int		i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while(str[i])
	{	
		if (str[i] == '=' && i > 0)//deve ritornare qui altrimenti non c'e var
			return (1);
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (0);
}

/*create new envp node and fill some fiedls*/
t_envp	*new_envp(char *arg, enum var_type type)
{
	t_envp	*new_node;
	char	**args;

	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (!new_node)
		return (0);
	new_node->input = ft_strdup(arg);
	if (!new_node->input)
		return (0);
	args = split_var(arg, '=');
	if (!args)
		return (0); //failure
	new_node->env = args[0];
	new_node->value = args[1];
	new_node->type = type;
	new_node->next = 0;
	new_node->prev = 0; //if we need prev
	return (new_node);
}

/*add envp node to the list*/
int	add_env(t_envp **envp, char *args, enum var_type type)
{
	t_envp	*new;
	t_envp	*ptr;

	if (!args)
		return (0);
	new = new_envp(args, type);
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

/*remove a node from the list*/
int	remove_envp(t_envp **envp, t_envp *to_rem)
{
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
	if (to_rem->value)
		free(to_rem->value);
	free(to_rem->input);
	free(to_rem);
	return (1); //success
}

/*return value of envp if it exists*/
char *get_env_value(char *name, t_data *data)
{
	t_envp	*ptr;

	if (!name)
		return (0);
	ptr = data->envp;
	while (ptr)
	{
		if (!ft_strncmp(ptr->env, name, ft_strlen(ptr->env) + 1))
			return (ptr->value);
		ptr = ptr->next;
	}
	return (0);
}