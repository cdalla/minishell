/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 16:49:42 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/29 17:36:03 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	read the token list
	divide the tokens in simple command
	recognize syntax errors

	SYNTAX ERROR TO CHECK
	| | | | | | | | 

	split the word from the symbol
	>outfile
	<infile
*/

/*
	parsing multi command
	create an array of single commands
	create a head node SIMPLE_CMD for each and fill his fields
*/

int	parse_multi_cmd(t_token **token, int n_pipes, t_scmd *multi_cmd)
{
	t_scmd	*cmd_ptr;
	t_token	*ptr;
	int		ret;

	ptr = *token;
	cmd_ptr = multi_cmd;
	while (ptr && n_pipes >= 0)
	{
		if (multi_cmd->cmd_name) //if head already created
		{
			cmd_ptr->next_cmd = new_scmd(SIMPLE_CMD); //add next_cmd
			if (!cmd_ptr->next_cmd)
				return (0);
			cmd_ptr = cmd_ptr->next_cmd;//move pointer to next cmd
		}
		ret = parse_loop(cmd_ptr, &ptr, 1);
		if (!ret)
			return (0);
		ret++;
		while (ret-- && ptr->next)
			ptr = ptr->next;
		n_pipes--;
	}
	return (1);
}

/*
	parsing single command
	create a head node SIMPLE_CMD and fill his fields
*/
t_scmd	*parse_simple_command(t_token *token)
{
	t_scmd	*cmd;

	cmd = new_scmd(SIMPLE_CMD); //create head of cmd node
	if (!token || !cmd)
		return (0); //error
	if (!parse_loop(cmd, &token, 0))
		return (0);
	return (cmd);
}

/*
	this function count the number of pipes present in the token list
	create a single command or multi command based on n_pipes
*/
t_scmd	*parser(t_data *data)
{
	t_scmd	*cmd;

	data->n_pipes = count_pipes(data->token);
	//printf ("n_pipes = %d\n", n_pipes); //testing purpose
	if (data->n_pipes)
	{
		cmd = new_scmd(SIMPLE_CMD);
		if (!cmd)
			return (0);
		if (!parse_multi_cmd(&data->token, data->n_pipes, cmd))
			return (0); //failed something free memory
		print_multi_cmd(cmd, data->n_pipes); //tester printing multi
	}
	else
	{
		cmd = parse_simple_command(data->token);
		if (!cmd)
			return (0);//failed something memory to free
		print_scmd(cmd);//tester printing single cmd
	}
	return (cmd);
}
