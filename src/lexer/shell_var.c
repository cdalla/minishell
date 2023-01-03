/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_var.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 12:39:13 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/03 15:49:40 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_first_token(t_token **token);
void	remove_token(t_token **token, t_token *to_rem);
char	**split_var(char *str, char c);
int		check_var_syntax(char *str);

/*delete var_declaration token from list*/
void	remove_var_declaration(t_data *data)
{
	t_token	*ptr;
	t_token	*to_rem;
	t_token	*prev;

	ptr = data->token;
	prev = 0;
	while (ptr)
	{
		if (check_var_syntax(ptr->word) && (!prev || prev->type == PIPE))
		{
			to_rem = ptr;
			if (ptr->next && ptr->next->type == PIPE)
				ptr = ptr->next->next;
			else
				ptr = ptr->next;
			remove_token(&data->token, to_rem);
		}
		else
		{
			prev = ptr;
			ptr = ptr->next;
		}
	}
}

/*check if PIPE present at the end after remove_var_decl*/
void	remove_extra_pipe(t_data *data)
{
	t_token	*ptr;

	ptr = data->token;
	while (ptr)
	{
		if (ptr->next && ptr->next->type == PIPE && !ptr->next->next)
		{
			ptr->next = 0;
			remove_token(&data->token, ptr->next);
			return ;
		}
		ptr = ptr->next;
	}
}

/*add or update var from token list*/
int	add_var(t_data *data, char *str, enum var_type type)
{
	char	**args;
	t_envp	*to_update;

	args = split_var(str, '=');
	if (!args)
		return (0);
	to_update = var_exist(data->envp, args[0]);
	if (to_update)
	{
		free(args[0]);
		update_var_value(data->envp, to_update, args[1], 0);
	}
	else
	{	
		free(args[0]);
		if (args[1])
			free(args[1]);
		free(args);
		if (!add_env(&data->envp, str, type))
			return (0);
	}
	return (1);
}

/*check presence of shell_var_declaration in token list*/
int	check_shell_var(t_data	*data)
{
	t_token	*ptr;

	ptr = data->token;
	if (ptr)
	{
		if (check_var_syntax(ptr->word))
		{
			if (!add_var(data, ptr->word, 1))
				return (0);
		}
		remove_var_declaration(data);
		remove_extra_pipe(data);
	}
	return (1);
}
