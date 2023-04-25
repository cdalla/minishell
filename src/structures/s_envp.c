/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   s_envp.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 10:55:25 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/04/25 12:32:12 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_var(char *str, char c);

/*create new envp node and fill some fields*/
t_envp	*new_envp(char *arg, enum e_var_type type)
{
	t_envp	*new;
	char	**args;

	new = (t_envp *)malloc(sizeof(t_envp));
	if (!new)
		return (0);
	args = split_var(arg, '=');
	if (!args)
		return (0);
	new->env = ft_strdup(args[0]);
	if (!new->env)
		return (free(args), free(args[1]), free(args), free(new), NULL);
	if (args[1])
	{
		new->value = ft_strdup(args[1]);
		if (!new->value)
			return (free(args[0]), free(args[1]), free(args), free(new), NULL);
	}
	else
		new->value = NULL;
	new->type = type;
	new->next = 0;
	new->prev = 0;
	return (free(args[0]), free(args[1]), free(args), new);
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
	free(to_rem);
	return (1);
}
