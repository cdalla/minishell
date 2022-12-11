/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_var.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 12:39:13 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/11 17:32:38 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void remove_first_token(t_token **token);
void remove_token(t_token **token, char *value);
char **split_var(char *str, char c);
int	check_var_syntax(char *str);

void	remove_var_declaration(t_data *data)
{
	t_token	*ptr;
	t_token	*to_rem;
	t_token	*prev;
	
	ptr = data->token;
	prev = 0;
	while (ptr)
	{
		if (check_var_syntax(ptr->word) && (!prev ||prev->type == PIPE)) //if ptr == var declaration
		{
			to_rem = ptr;
			if (ptr->next && ptr->next->type == PIPE)//if next is pipe i skip 2
				ptr = ptr->next->next;
			else									//else skip one
				ptr = ptr->next;
			remove_token(&data->token, to_rem->word);
		}
		else
		{
			prev = ptr;
			ptr = ptr->next;
		}
	}
}

int	var_exist(t_envp *envp, char *name, char *value)
{
	t_envp	*ptr;

	ptr = envp;
	while (ptr)
	{
		if (!ft_strncmp(ptr->env, name, ft_strlen(ptr->env) + 1))
		{
			free(ptr->value);
			free(name);
			ptr->value = value;
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

int	add_shell_var(t_data *data, t_token *token)
{
	char	**args;
	
	(void)data;
	args = split_var(token->word, '=');
	if (!args)
		return (0); //malloc error
	if (!var_exist(data->envp, args[0], args[1]))
	{	
		free(args[0]);
		if (args[1])
			free(args[1]);
		free(args);
		if (!add_env(&data->envp, token->word, 1))
			return (0);
	}
	return (1);
}

int	check_shell_var(t_data	*data)
{
	t_token	*ptr;

	ptr = data->token;
	if (check_var_syntax(ptr->word))
	{
		if (!add_shell_var(data, ptr))
			return (0); //malloc fail
	}
	remove_var_declaration(data);
	return (1);
}