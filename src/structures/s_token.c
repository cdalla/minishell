/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   s_token.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 11:39:35 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/16 13:26:58 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*create new token node*/
t_token	*new_token(char *word, int type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (0); //failure
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
		return (0); //failure
	if (!*token) //if token list empty
		*token = new;
	else
	{
		ptr = *token;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	return (1); //success
}

/*TO REMOVE*/
void	print_tokens(t_token *token)
{
	t_token	*ptr;

	ptr = token;
	while (ptr)
	{
		printf("\"%s\" type = %d\n", ptr->word, ptr->type);
		ptr = ptr->next;
	}
}

