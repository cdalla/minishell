/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 11:32:21 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/03 15:38:33 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*if var exist, delete it from envp list*/
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
		return (print_err_msg(108, "unset"));
	return (0);
}
