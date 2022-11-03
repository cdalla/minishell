/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 10:47:04 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/03 13:04:33 by cdalla-s      ########   odam.nl         */
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
		
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	env_save(&data.envp, envp);
}