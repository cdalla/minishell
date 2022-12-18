/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 09:50:22 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/18 16:12:18 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	-modify type of shell var if args -> <key>=<value>, use check_var_syntax && one single arg
		-<key>=<value> -> update value if var exist, else add new ENV 
		-only <key> -> add from SHELL to ENV if the variable exist
	-list existing var -> printf all type ENV if the form "declare -x <key>=<value>"


	FIX PRINTING MUST BE IN ORDER
*/

int	count_list_size(t_envp *envp)
{
	int		size;
	t_envp	*ptr;

	size = 0;
	ptr = envp;
	while (ptr)
	{
		if (ptr->type == ENV)
			size++;
		ptr = ptr->next;
	}
	return (size);
}

void	print_declare(t_envp **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i]->type == ENV)
		{
			printf("declare -x %s=", ptr[i]->env);
			if (ptr[i]->value)
				printf("\"%s\"\n", ptr[i]->value);
			else
				printf("\n");
		}
		i++;
	}
}

int	is_in_array(t_envp *ptr, t_envp **array)
{
	int	i;

	i = 0;
	if	(!array)
		return (0);
	while (array[i])
	{
		if (array[i] == ptr)
			return (1);
		i++;
	}
	return (0);
}

t_envp	*find_min(t_envp *envp, t_envp **array)
{
	t_envp	*ptr;

	ptr = envp;
	while (ptr)
	{
		if (ptr->type == ENV && !is_in_array(ptr, array))
			return (ptr);
		ptr = ptr->next;
	}
	return(0);
}
//TO FIX AND  PUT IN ORDER
/*print env var, with declare -x before*/
int	order_envp(t_envp *envp)
{
	t_envp	*ptr;
	t_envp	*min;
	t_envp	**copy;
	int		size;
	int 	i;

	copy = 0;
	i = 0;
	size = count_list_size(envp);
	if (size)
		copy = (t_envp **)malloc((size + 1) * sizeof(t_envp *));
	if (!copy)
		return (0); //malloc failed (or not envp)
	copy[size] = 0;
	while (i < size)
	{
		ptr = envp;
		min = find_min(envp, copy); //return first element not in array
		while (ptr)
		{
			if (ptr->type == ENV && !is_in_array(ptr, copy)
				&& (ft_strcmp(ptr->value, min->value) < 0)) //if 
			{
				min = ptr;
			}
			ptr = ptr->next;
		}
		//printf("%s\n", min->env);
	 	copy[i] = min;
		i++;
	}
	print_declare(copy);
	return (1);
}

/*no args print, <key> update type, <key>=<value> add new envp*/
int	export(t_scmd *args, t_data *data)
{
	t_envp	*to_export;

	if (!args)
	{
		if (!order_envp(data->envp))
			return (0); //malloc failed
	}
	else if (!args->next_arg && check_var_syntax(args->value)) //update or add
	{
		if (!add_var(data, args->value, 2))
			return (0); //malloc failed
	}
	else if (!args->next_arg && !ft_strchr(args->value, '=')) //change type if exist
	{
		to_export = var_exist(data->envp, args->value);
		if (to_export)
			update_var_value(data->envp, to_export, 0, 1);
	}
	else
		printf("export: syntax error\n");
	return (1); //return errno
}
