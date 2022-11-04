/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 10:47:04 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/04 12:23:52 by cdalla-s      ########   odam.nl         */
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

	env_save(&data.envp, envp);
	prompt_call(&data);
	return (0);	
}