#include "../minishell.h"

char **cpy_list_env(t_envp *list, int size)
{
	int		i;
	t_envp	*ptr;
	char	**array;
	
	i = 0;
	array = (char **)malloc((size + 1) * sizeof(char *));
	if (!array)
		return (0); //malloc error
	ptr = list;	
	while (ptr && i < size)
	{
		array[i] = ft_strdup(ptr->input);
		if (!array[i])
			return (0); //malloc error free
		i++;
		ptr = ptr->next;
	}
	array[i] = 0;
	return (array);
}

char **ls_toarr_env(t_envp *list)
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

char **cpy_list_args(t_scmd *list, int size)
{
	int		i;
	t_scmd	*ptr;
	char	**array;
	
	i = 0;
	array = (char **)malloc((size + 1) * sizeof(char *));
	if (!array)
		return (0); //malloc error
	ptr = list;	
	while (ptr && i < size)
	{
		array[i] = ft_strdup(ptr->value);
		if (!array[i])
			return (0); //malloc error free
		i++;
		ptr = ptr->next_arg;
	}
	array[i] = 0;
	return (array);
}

char **ls_toarr_args(t_scmd *list)
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
	return (cpy_list_args(list, size));
}