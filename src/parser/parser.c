/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 16:49:42 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/21 16:46:58 by cdalla-s      ########   odam.nl         */
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

int	count_pipes(t_token *token)
{
	t_token	*ptr;
	int		count;

	count = 0;
	ptr = token;
	while (ptr)
	{
		if (ptr->type == PIPE)
			count++;
		ptr = ptr->next;
	}
	return (count);
}


//check if this function is actually modifying the cmd pointer value or not
//but i think it is correct XD
int	parse_single_token(t_token *ptr, t_scmd *cmd)
{
	t_scmd	*arg;
	int		ret;

	ret = 0;
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
		else if (ptr->type == HEREDOC)
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
	t_token	*ptr;
	int		i;
	int		ret;

	cmd_line = (t_scmd **)malloc((n_pipes + 2) * sizeof(t_scmd *));// if 1 pipe == 2 cmd, plus null pointer at the end
	if (!cmd_line)
		return (0); //malloc failed
	i = 0;
	ptr = token;
	while (token && i <= n_pipes)
	{	
		cmd_line[i] = new_scmd(SIMPLE_CMD);
		if (!ptr || !cmd_line[i])
			return (0); //failed and free memory
		while (token->type != PIPE && ptr)
		{
			ret = parse_single_token(ptr, cmd_line[i]);
			if (!ret)
				return (0); //error free memory
			while (ret--)
				ptr = ptr->next;
		}
		if (ptr->next)
			ptr = ptr->next;
		i++;
	}
	cmd_line[n_pipes + 1] = NULL;
	return (cmd_line);
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
	cmd = new_scmd(SIMPLE_CMD); //create head of cmd node
	if (!ptr || !cmd)
		return (0); //error
	while (ptr && ptr->type != PIPE)
	{
		ret = parse_single_token(ptr, cmd);
		if (!ret)
			return (0); //error free memory
		while (ret-- != 0 && ptr)
		{
			ptr = ptr->next;
			//ret--;
		}
	}
	return (cmd);
}

int	parser(t_data *data)
{
	t_scmd	**cmd_line = NULL;
	t_scmd	*single_cmd = NULL;
	int		n_pipes;
	
	
	n_pipes = count_pipes(data->token);
	printf ("n_pipes = %d\n", n_pipes);
	//print_tokens(data->token);
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
		{
			printf("single cmd not returned\n");
			return (0);
		} //failed something memory to free
		print_scmd(single_cmd);
	}
	return (1);
}
