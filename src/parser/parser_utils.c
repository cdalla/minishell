/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 11:44:27 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/17 22:57:55 by cdalla-s      ########   odam.nl         */
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

/*add type infile and outfile to CMD redirection linked lists*/
// int	parse_red(t_token *ptr, t_scmd *cmd)
// {
// 	int	ret;

// 	ret = 0;
// 	if (ptr->type == READ)
// 		ret = add_infile(cmd, READ, ptr->next->word);
// 	else if (ptr->type == HEREDOC)
// 		ret = add_infile(cmd, HERED, ptr->next->word);
// 	else if (ptr->type == REDO)
// 		ret = add_outfile(cmd, WRITE, ptr->next->word);
// 	else if (ptr->type == REDOA)
// 		ret = add_outfile(cmd, APPEND, ptr->next->word);
// 	return (ret);
// }

/*eval token content, set corresponding SCMD field*/
// int	parse_single_token(t_token *ptr, t_scmd *cmd)
// {
// 	t_scmd	*arg;
// 	int		ret;

// 	ret = 0;
// 	if (ptr->type == WORD)
// 	{
// 		arg = new_scmd(ARGUMENT);
// 		if (!arg)
// 			return (0);
// 		set_scmd_value(arg, ptr->word);
// 		add_scmd_arg(cmd, arg);
// 		return (1); //success with 1 position to skip in token list	
// 	}
// 	else
// 	{
// 		ret = parse_red(ptr, cmd);
// 		if (!ret)
// 			return (0); //errors
// 		return (2); //success and skip 2 position
// 	}
// }

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
		if (!add_file(cmd, ptr->type, ptr->next->word))
			return (0); //errors
		return (2); //success and skip 2 position
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
	while (ptr && ptr->type != PIPE) //put this loop in another function
	{
		ret = parse_single_token(ptr, cmd);
		if (!ret)
			return (0); //error free memory
		ret_line += ret;
		while (ret-- != 0 && ptr)
			ptr = ptr->next;
	}
	if (line)
		return (ret_line);
	return (1);
}
