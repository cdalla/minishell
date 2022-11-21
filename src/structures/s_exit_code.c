/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   s_exit_code.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 12:03:48 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/21 12:11:32 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	struct for exit code???
	pointer to s_exit_code in main struct
	create a new exit code node
	add node to the list

	DO WE NEED OTHER FUNCTIONS????
	PRINT?
	MODIFY?

*/

typedef struct s_excode
{
    int				code;
    char			*cmd;
    struct s_excode	*next;
    struct s_excode	*prev;
}   			t_excode;

t_excode	*new_excode(char *cmd, int code)
{
	t_excode	*new_excode;

	new_excode = (t_excode *)malloc(sizeof(t_excode));
	if (!new_excode)
		return (0); //failure
	new_excode->code = code;
	new_excode->cmd = cmd;
	new_excode->prev = 0;
	new_excode->next = 0;
	return (new_excode);
}

int	add_excode(t_excode **exit_code, char *cmd, int code)
{
	t_excode	*new;
	t_excode	*ptr;

	new = new_excode(cmd, code);
	if (!new)
		return (0); //failure
	if (!*exit_code) //list empty
		*exit_code = new;
	else
	{
		ptr = *exit_code;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	return (1); //success
}