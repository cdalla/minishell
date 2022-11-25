/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 10:47:04 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/25 12:40:32 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	create structures
	save env into envp structure
	call to:
	LEXER 
	PARSER
	EXPANDER
	EXECUTER
*/

int	add_env(t_envp **envp, char *args);
void    print_env_var(t_envp *envp);

int	env_save(t_envp **s_envp, char **envp)
{
	int	i;

	i = 0;
	while(envp[i])
	{
		if (!add_env(s_envp, envp[i]))
			return (0); //failure and free all the malloced mem
		i++;
	}
	return (1); //success
}

/*
	initialize env list
	launch prompt
	scan input
	check for lexical errors
*/
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
	env_save(&data.envp, envp);
	//print_env_var(data.envp); //WE SAVED CORRECTLY THE INITIAL CONF OF ENV
	prompt_call(&data);
	exit(0);
	return (0);
}