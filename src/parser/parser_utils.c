/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 11:44:27 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/03 15:58:40 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*count PIPE presence*/
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

/*eval token content, set corresponding SCMD field*/
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
		return (1);
	}
	else
	{
		if (!add_file(cmd, ptr->type, ptr->next->word))
			return (0);
		return (2);
	}
}

/*loop token list, divide when find pipes*/
int	parse_loop(t_scmd *cmd, t_token **token, int line)
{
	int		ret;
	int		ret_line;
	t_token	*ptr;

	ret_line = 0;
	ptr = *token;
	while (ptr && ptr->type != PIPE)
	{
		ret = parse_single_token(ptr, cmd);
		if (!ret)
			return (0);
		ret_line += ret;
		while (ret-- != 0 && ptr)
			ptr = ptr->next;
	}
	if (line)
		return (ret_line);
	return (1);
}
