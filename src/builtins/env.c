/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 11:26:05 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/02 16:58:17 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*call env var printing*/
int	env(t_scmd *args, t_data *data)
{
	if (!args)
		print_env_var(data->envp);
	else
		return (print_err_msg(108));
	return(1); //errno?
}