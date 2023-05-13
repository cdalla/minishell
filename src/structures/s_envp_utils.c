/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   s_envp_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/11 12:10:52 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/05/04 02:14:57 by lisa          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

/*loop envp list and return ptr if env exist*/
t_envp	*var_exist(t_envp *envp, char *name)
{
	t_envp	*ptr;

	ptr = envp;
	while (ptr)
	{
		if (!ft_strncmp(ptr->env, name, ft_strlen(ptr->env) + 1))
			return (ptr);
		ptr = ptr->next;
	}
	return (0);
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
		{
			if (ptr->value)
				return (ptr->value);
			else
				return ("\0");
		}
		ptr = ptr->next;
	}
	return (0);
}

/*find correct envp based on value, set new value or new type*/
int	update_var_value(t_envp *envp, t_envp *var, char *value, int type)
{
	t_envp	*ptr;

	ptr = envp;
	while (ptr)
	{
		if (ptr == var)
		{
			if (type)
				ptr->type = type;
			else
			{
				free(ptr->value);
				ptr->value = value;
			}
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

/*print all envp type ENV*/
void	print_env_var(t_envp *envp)
{
	t_envp	*ptr;

	ptr = envp;
	while (ptr)
	{
		if (ptr->type == ENV && ptr->value)
		{
			printf("%s=", ptr->env);
			if (ptr->value)
				printf("%s\n", ptr->value);
			else
				printf("\n");
		}
		ptr = ptr->next;
	}
}
