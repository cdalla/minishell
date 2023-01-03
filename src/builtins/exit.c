/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/02 17:29:10 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/03 11:51:02 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_f(t_scmd *args, t_data *data)
{
	int	value;

	(void)data;
	value = 0;
	printf("exit\n");
	if (args && args->value)
		value = ft_atoi(args->value);
	if (args->next_arg)
		return (print_err_msg(109, "exit"));
	exit (value);
}
