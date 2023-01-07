/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   s_envp.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 10:55:25 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/07 14:11:49 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_var(char *str, char c);

/*check var_name correct syntax*/
int	check_var_syntax(char *str)
{
	int		i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i])
	{	
		if (str[i] == '=' && i > 0)
			return (1);
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (0);
}

/*create new envp node and fill some fiedls*/
t_envp	*new_envp(char *arg, enum e_var_type type)
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
		return (0);
	new_node->env = args[0];
	new_node->value = args[1];
	new_node->type = type;
	new_node->next = 0;
	new_node->prev = 0;
	return (new_node);
}

/*add envp node to the list*/
int	add_env(t_envp **envp, char *args, enum e_var_type type)
{
	t_envp	*new;
	t_envp	*ptr;

	if (!args)
		return (0);
	new = new_envp(args, type);
	if (!new)
		return (0);
	if (!*envp)
		*envp = new;
	else
	{
		ptr = *envp;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
		new->prev = ptr;
	}
	return (1);
}

/*remove a node from the list*/
int	remove_envp(t_envp **envp, t_envp *to_rem)
{
	if (!to_rem->prev && to_rem->next)
	{
		to_rem->next->prev = 0;
		*envp = to_rem->next;
	}
	else if (to_rem->prev && !to_rem->next)
		to_rem->prev->next = 0;
	else if (to_rem->prev && to_rem->next)
	{
		to_rem->next->prev = to_rem->prev;
		to_rem->prev->next = to_rem->next;
	}
	free(to_rem->env);
	if (to_rem->value)
		free(to_rem->value);
	free(to_rem->input);
	free(to_rem);
	return (1);
}

/*return value of envp if it exists*/
char	*get_env_value(char *name, t_data *data)
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
