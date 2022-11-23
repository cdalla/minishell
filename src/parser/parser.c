/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 16:49:42 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/23 00:32:21 by lisa          ########   odam.nl         */
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
t_scmd **parse_cmd_line(t_token **token, int n_pipes)
{
	t_scmd	**cmd_line;
	t_token	*ptr;
	int 	ret;
	int		i;
	
	cmd_line = (t_scmd **)malloc((n_pipes + 2) * sizeof(t_scmd *));// if 1 pipe == 2 cmd, plus null pointer at the end
	if (!cmd_line)
		return (0); //malloc failed
	i = 0;
	ptr = *token;
	while (ptr && i <= n_pipes)
	{	
		cmd_line[i] = new_scmd(SIMPLE_CMD);
		if (!*token || !cmd_line[i])
			return (0); //failed and free memory
		ret = parse_loop(cmd_line[i], &ptr, 1);
		if (!ret)
			return (0);
		ret++;
		while (ret-- && ptr->next)
			ptr = ptr->next;
		i++;
	}
	cmd_line[n_pipes + 2] = NULL;
	return (cmd_line);
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

int	executer_single(t_scmd *cmd, t_data *data);
/*
	this function count the number of pipes present in the token list
	create a single command or multi command based on n_pipes
*/
int	parser(t_data *data)
{
	t_scmd	**cmd_line = NULL;
	t_scmd	*single_cmd = NULL;
	int		n_pipes;
	int		i;
	
	i = 0;
	n_pipes = count_pipes(data->token);
	printf ("n_pipes = %d\n", n_pipes);
	//print_tokens(data->token);
	if (n_pipes)
	{
		cmd_line = parse_cmd_line(&data->token, n_pipes);
		if (!cmd_line)
			return (0); //failed something free memory
		while(i <= n_pipes)//tester printing cmd_line content
		{
			printf("CMD %d\n", i+1);
			print_scmd(cmd_line[i]);
			i++;
		}
	}
	else
	{
		single_cmd = parse_simple_command(data->token);
		if (!single_cmd)
			return (0);//failed something memory to free
		executer_single(single_cmd, data);
		//print_scmd(single_cmd);//tester printing single cmd
	}
	return (1);
}
