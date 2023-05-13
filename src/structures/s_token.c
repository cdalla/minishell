/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   s_token.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 11:39:35 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/04/25 16:03:46 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*create new token node*/
t_token	*new_token(char *word, int type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (0);
	new_token->word = word;
	new_token->type = type;
	new_token->next = 0;
	return (new_token);
}

/*append token node to token list*/
int	add_token(t_token **token, char *word, int type)
{
	t_token	*new;
	t_token	*ptr;

	new = new_token(word, type);
	if (!new)
		return (0);
	if (!*token)
		*token = new;
	else
	{
		ptr = *token;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	return (1);
}
