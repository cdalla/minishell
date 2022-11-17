/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 16:49:42 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/17 14:14:06 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	read the token list
	divide the tokens in simple command
	recognize syntax errors
*/

/*
	SYNTAX ERROR TO CHECK

	| | | | | | | | 
*/

/*
	while (token->type == 1)
	{
		insert the first as cmd
		insert the rest in a double array as arguments of the command
	}
*/

int	count_pipes(t_data *token)
{
	t_token	*ptr;
	int		count;

	count = 0;
	while (ptr)
	{
		if (ptr->type == PIPE)
			count++;
		ptr = ptr->next;
	}
	return (count);
}

int	parser(t_data *data)
{
	t_scmd	**cmd_line;
	t_scmd	*single_cmd;
	int		n_pipes;

	n_pipes = count_pipes(data->token);
	if (n_pipes)
	{
		cmd_line = parse_cmd_line(data->token, n_pipes);
		if (!cmd_line)
			return (0); //failed something free memory
	}
	else
	{
		single_cmd = parse_simple_command(data->token);
		if (!single_cmd)
			return (0); //failed something memory to free
	}
}

t_scmd	*parse_single_token(t_token *ptr, t_scmd *cmd)
{
	t_scmd	*arg;
	int		ret;

	cmd = new_scmd(SIMPLE_CMD);
	if (!ptr || !cmd)
		return (0); //error
	if (ptr->type == WORD)
	{
		arg = new_scmd(ARGUMENT);
		if (!arg)
			return (0);
		set_scmd_value(arg, ptr->word);
		add_scmd_arg(cmd, arg);
		return (1); //success with 1 position to skip in token list
	}
	else
	{
		if (ptr->type == REDI)
		ret = add_infile(cmd, READ, ptr->next->word);
		else if (ptr->type == HERED)
		ret = add_infile(cmd, HERED, ptr->next->word);
		else if (ptr->type == REDO)
		ret = add_outfile(cmd, WRITE, ptr->next->word);
		else if (ptr->type == REDOA)
		ret = add_outfile(cmd, APPEND, ptr->next->word);
		if (!ret)
			return (0); //errors
		return (2); //success and skip 2 position
	}
}

t_scmd **parse_cmd_line(t_token *token, int n_pipes)
{
	t_scmd	**cmd_line;

	cmd_line = (t_scmd **)malloc((n_pipes + 1) * sizeof(t_scmd *));
	if (!cmd_line)
		return (0); //malloc failed
}

/*
	!!!PROBLEM!!! if we have more simple_cmd we need to keep trace where we are in the token list
	this function create a simple command head
	connected to it there will be first the cmd_name then all the arguments

	int the caller count how many pipes and give a number of pipes == number of commands
*/

t_scmd	*parse_simple_command(t_token *token)
{
	t_scmd	*cmd;
	t_token	*ptr;
	int		ret;

	ptr = token;
	cmd = new_scmd(SIMPLE_CMD);
	if (!ptr || !cmd)
		return (0); //error
	while (ptr->type != PIPE && ptr)
	{
		ret = parse_single_token(ptr, cmd);
		while (ret--)
			ptr = ptr->next;
	}
	return (cmd);
}