/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 09:50:22 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/13 17:05:49 by cdalla-s      ########   odam.nl         */
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

void	print_declare(t_envp *envp)
{
	t_envp	*ptr;

	ptr = envp;
	while (ptr)
	{
		if (ptr->type == ENV)
		{
			printf("declare -x %s=", ptr->env);
			if (ptr->value)
				printf("%s\n", ptr->value);
			else
				printf("\n");
		}
		ptr = ptr->next;
	}
}

int	export(t_scmd *args, t_data *data)
{
	t_envp	*to_export;

	if (!args)
		print_declare(data->envp);
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
