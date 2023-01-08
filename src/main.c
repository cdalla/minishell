/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 10:47:04 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/08 16:15:33 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(t_data *data)
{
	t_envp	*ptr;
	t_envp	*next;

	ptr = data->envp;
	while (ptr)
	{
		next = ptr->next;
		if (ptr->env)
			free(ptr->env);
		if (ptr->value)
			free(ptr->value);
		if (ptr->input)
			free(ptr->input);
		free(ptr);
		ptr = next;
	}
	data->envp = NULL;
}

/*increase SHLVL in envp everytime ./minishell is called*/
int	incr_shell_lvl(t_data *data)
{
	char	*old_lvl;
	char	*new_lvl;

	old_lvl = get_env_value("SHLVL", data);
	new_lvl = ft_itoa(ft_atoi(old_lvl) + 1);
	if (!new_lvl)
		return (0);
	update_var_value(data->envp, var_exist(data->envp, "SHLVL"), new_lvl, 0);
	return (1);
}

/*save initial configuration of env vars*/
int	env_save(t_envp **s_envp, char **envp, t_data *data)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!add_env(s_envp, envp[i], 2))
			return (0);
		i++;
	}
	if (!incr_shell_lvl(data))
		return (0);
	return (1);
}

void	exit_check(void)
{
	system("leaks -q minishell");
}

/*create data struct instance, fill envp, start cmd line*/
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	//atexit(exit_check);
	if (argc > 2 || !argv)
		return (0);
	(void)argc;
	(void)argv;
	data.envp = NULL;
	data.token = NULL;
	data.exit_code = 0;
	if (!env_save(&data.envp, envp, &data))
		return (0);
	// if (!prompt_call(&data))
	// 	return (0);
	prompt_call(&data);
	free_envp(&data);
	return (0);
}
