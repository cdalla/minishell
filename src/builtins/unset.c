/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 11:32:21 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/13 11:40:04 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset(t_scmd *args, t_data *data)
{
	t_envp	*to_rem;

	if (args->value && !args->next_arg)
	{
		to_rem = var_exist(data->envp, args->value);
		if (to_rem)
			remove_envp(&data->envp, to_rem);
	}
	else
		printf("unset: syntax error\n");
	return (1); //return errno
}