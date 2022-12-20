/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/20 11:39:34 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/20 11:43:08 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*count envp list elements*/
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

/*check if element is already sorted in the array*/
int	is_in_array(t_envp *ptr, t_envp **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
	{
		if (array[i] == ptr)
			return (1);
		i++;
	}
	return (0);
}

/*find next element not present in array for comparison*/
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
	return (0);
}

/*fill sorted array with pointers to envp list elements*/
t_envp	**fill_array(int size, t_envp *envp)
{
	t_envp	*ptr;
	t_envp	*min;
	t_envp	**copy;
	int		i;

	i = 0;
	copy = (t_envp **)malloc((size + 1) * sizeof(t_envp *));
	if (!copy)
		return (0);
	copy[size] = 0;
	while (i < size)
	{
		ptr = envp;
		min = find_min(envp, copy); //return first element not in array
		while (ptr)
		{
			if (ptr->type == ENV && !is_in_array(ptr, copy)
				&& (ft_strcmp(ptr->env, min->env) < 0)) //if 
				min = ptr;
			ptr = ptr->next;
		}
		copy[i] = min;
		i++;
	}
	return (copy);
}
