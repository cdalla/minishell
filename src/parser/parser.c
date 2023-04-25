/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 16:49:42 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/04/25 13:41:02 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
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
		if (multi_cmd->cmd_name)
		{
			cmd_ptr->next_cmd = new_scmd(SIMPLE_CMD);
			if (!cmd_ptr->next_cmd)
				return (0);
			cmd_ptr = cmd_ptr->next_cmd;
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

/*	create a head node SIMPLE_CMD and fill his fields*/
t_scmd	*parse_simple_command(t_token *token)
{
	t_scmd	*cmd;

	if (!token)
		return (0);
	cmd = new_scmd(SIMPLE_CMD);
	if (!cmd)
		return (0);
	if (!parse_loop(cmd, &token, 0))
		return (0);
	return (cmd);
}

/*count PIPES, call multi line or single cmd creation*/
t_scmd	*parser(t_data *data)
{
	t_scmd	*cmd;

	data->n_pipes = count_pipes(data->token);
	if (data->n_pipes)
	{
		cmd = new_scmd(SIMPLE_CMD);
		if (!cmd)
			return (0);
		if (!parse_multi_cmd(&data->token, data->n_pipes, cmd))
			return (0);
	}
	else
	{
		cmd = parse_simple_command(data->token);
		if (!cmd)
			return (0);
	}
	return (cmd);
}
