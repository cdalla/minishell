/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   s_envp_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/11 12:10:52 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/08 13:30:51 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*split input str into the envp args[2]*/
int	split_args(char **split, char *str, char c)
{
	int		w_len;

	w_len = 0;
	while (*(str + w_len) != c && *(str + w_len))
		w_len++;
	if (w_len)
		split[0] = ft_substr(str, 0, w_len);
	if (!split[0])
		return (0);
	str += (w_len + 1);
	w_len = 0;
	while (*(str + w_len))
		w_len++;
	if (w_len)
	{
		split[1] = ft_substr(str, 0, w_len);
		if (!split[1])
		{
			free(split[0]);
			return (0);
		}
	}
	else
		split[1] = 0;
	return (1);
}

/*create envp args[2] for name_env and value_env*/
char	**split_var(char *str, char c)
{
	char	**split;

	split = (char **)malloc(3 * sizeof(char *));
	if (!split)
		return (0);
	split_args(split, str, c);
	if (!split)
	{
		free(split);
		return (0);
	}
	split[2] = 0;
	return (split);
}

/*loop envp list and return 1 if env exist*/
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
				ptr->type = ENV;
			else
			{
				//free(ptr->input);
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
		if (ptr->type == ENV)
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
