/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 16:49:42 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/16 14:11:18 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	read the token list
	divide the tokens in simple command
	recognize syntax errors
*/

/*
	while (token->type == 1)
	{
		insert the first as cmd
		insert the rest in a double array as arguments of the command
	}
*/

// int	parser(t_data *data)
// {
	
// }

/*
	!!!PROBLEM!!! if we have more simple_cmd we need to keep trace where we are in the token list
	this function create a simple command head
	connected to it there will be first the cmd_name then all the arguments


	int the caller count how many pipes and give a number of pipes == number of commands
*/
t_scmd	*parse_simple_command(t_token *token)
{
	t_scmd	*cmd;
	t_scmd	*arg;

	cmd = new_scmd(SIMPLE_CMD);
	if (!token || !cmd)
		return (0); //error
	while (token->type != PIPE)
	{
		arg = new_scmd(ARGUMENT);
		if (!arg)
			return (0);
		set_scmd_value(arg, token->word);
		add_scmd_arg(cmd, arg);
	}
	return (cmd);
}