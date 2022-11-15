/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   s_token.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 11:39:35 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/15 13:31:08 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	pointer to s_token list in main struct
	create a new token
	add a new token to the list

	!!!CREATE AN ENUM LIST FOR TOKEN TYPES!!!

	-we need a function who call token creation where after recognizing the type
	and pass it as parameter
	-or we do type-recognition in the node creation
*/

//without recognition
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

int add_token(t_token **token, char *word, int type)
{
	t_token	*new;
	t_token	*ptr;

	new = new_token(word, type);
	if (!new)
		return (0); //failure
	if(!*token) //if token list empty
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
