/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 10:47:04 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/16 13:36:18 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*save initial configuration of env vars*/
int	env_save(t_envp **s_envp, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!add_env(s_envp, envp[i], 2))
			return (0); //failure and free all the malloced mem
		i++;
	}
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
	data.exit_code = NULL;
	if (!env_save(&data.envp, envp))
		return (0); //malloc fail
	if (!prompt_call(&data))
		return (0); // malloc fail
	exit(0);
	return (0);
}
