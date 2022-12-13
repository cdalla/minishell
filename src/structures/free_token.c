/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_token.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/11 13:28:29 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/13 09:36:11 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_token(t_token *to_rem)
{
	free(to_rem->word);
	free(to_rem);
}

void set_next_token(t_token **token, t_token *ptr, t_token *prev)
{
	if (ptr->next && ptr->next->type == PIPE)
	{
		if (prev)
			prev->next = ptr->next->next;
		else
			*token = ptr->next->next;
		free_token(ptr->next);
	}
	else
	{
		if (prev)
			prev->next = ptr->next;
		else
			*token = ptr->next;
	}
}

void remove_token(t_token **token, t_token *to_rem)
{
	t_token	*ptr;
	t_token	*prev;

	prev = 0;
	ptr = *token;
	while (ptr)
	{
		if (ptr == to_rem)
		{
			set_next_token(token, ptr, prev);
			free_token(ptr);
			return ;
		}
		prev = ptr;
		ptr = ptr->next;
	}
}

void	free_tokens(t_data *data)
{
	t_token	*ptr;
	t_token	*next;

	ptr = data->token;
	while (ptr)
	{
		next = ptr->next;
		free_token(ptr);
		ptr = next;
	}
	data->token = NULL;
}