/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve_array.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/25 12:50:28 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/21 13:50:15 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*duplicate every list value in a array[]*/
char	**cpy_list_env(t_envp *ptr, int size)
{
	int		i;
	char	**array;

	i = 0;
	array = (char **)malloc((size + 1) * sizeof(char *));
	if (!array)
		return (0); //malloc error
	while (ptr && i < size)
	{
		array[i] = ft_strdup(ptr->input);
		if (!array[i])
		{
			while (--i >= 0)
				free(array[i]);
			free(array);
			return (0); //malloc error free
		}
		i++;
		ptr = ptr->next;
	}
	array[i] = 0;
	return (array);
}

/*count list size and call copy function*/
char	**ls_toarr_env(t_envp *list)
{
	t_envp	*ptr;
	int		size;

	size = 0;
	ptr = list;
	while (ptr)
	{
		size++;
		ptr = ptr->next;
	}
	return (cpy_list_env(list, size));
}

/*duplicate every list value in a array[]*/
char	**cpy_list_args(t_scmd *ptr, int size, char *cmd_name)
{
	int		i;
	char	**array;

	i = 1;
	array = (char **)malloc((size + 2) * sizeof(char *));
	if (!array)
		return (0); //malloc error
	array[0] = ft_strdup(cmd_name);
	if (!array[0])
		return (0);
	while (ptr && i <= size)
	{
		array[i] = ft_strdup(ptr->value);
		if (!array[i])
		{
			while (--i >= 0)
				free(array[i]);
			free(array);
			return (0); //malloc error free
		}
		i++;
		ptr = ptr->next_arg;
	}
	array[i] = 0;
	return (array);
}

/*count list size and call copy function*/
char	**ls_toarr_args(t_scmd *list, char *cmd_name)
{
	t_scmd	*ptr;
	int		size;

	size = 0;
	ptr = list;
	while (ptr)
	{
		size++;
		ptr = ptr->next_arg;
	}
	return (cpy_list_args(list, size, cmd_name));
}
