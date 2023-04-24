/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 09:50:22 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/04/24 18:29:13 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		count_list_size(t_envp *envp);
t_envp	**fill_array(int size, t_envp *envp);

/*print in the correct format for export command*/
void	print_declare(t_envp **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i]->type == ENV)
		{
			printf("declare -x %s", ptr[i]->env);
			if (ptr[i]->value)
				printf("=\"%s\"\n", ptr[i]->value);
		}
		i++;
	}
}

/*order envp list in an array before printing*/
int	order_envp(t_envp *envp)
{
	t_envp	**copy;
	int		size;

	copy = 0;
	size = count_list_size(envp);
	if (size)
		copy = fill_array(size, envp);
	if (!copy)
		return (0);
	print_declare(copy);
	free(copy);
	return (1);
}

/*no args print, <key> update type, <key>=<value> add new envp*/
int	export(t_scmd *args, t_data *data)
{
	t_envp	*to_export;

	if (!args) //print vars
	{
		if (!order_envp(data->envp))
			return (print_err_msg(107, "export"));
	}
	else if (!args->next_arg && check_var_syntax(args->value)) //add new or update if there is =
	{
		if (!add_var(data, args->value, 2))
			return (print_err_msg(107, "export"));
	}
	else if (!args->next_arg && !ft_strchr(args->value, '=')) //update value
	{
		to_export = var_exist(data->envp, args->value);
		if (to_export)
			update_var_value(data->envp, to_export, 0, 2);
		else if (!add_env(&data->envp, args->value, 2))
			return (print_err_msg(107, "export"));
	}
	else
		return (print_err_msg(108, "export"));
	return (0);
}
