/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 10:47:04 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/06 11:29:27 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (0); //failure and free all the malloced mem
		i++;
	}
	if (!incr_shell_lvl(data))
		return (0);
	return (1); //success
}

/*create data struct instance, fill envp, start cmd line*/
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc > 2 || !argv)
		return (0);
	(void)argc;
	(void)argv;
	data.envp = NULL;
	data.token = NULL;
	data.exit_code = 0;
	if (!env_save(&data.envp, envp, &data))
		return (0); //malloc fail
	if (!prompt_call(&data))
		return (0);
	exit(0);
	return (0);
}
