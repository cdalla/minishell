/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/02 17:29:10 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/05/04 14:15:06 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_f(t_scmd *args, t_data *data)
{
	int	value;

	(void)data;
	value = 0;
	write(2, "exit\n", 5);
	if (args && !check_alpha(args->value))
	{
		print_err_msg(110, "exit");
		value = 255;
	}
	else if (args && args->next_arg)
		return (print_err_msg(109, "exit"));
	else if (args && args->value)
			value = ft_atoi(args->value);
	exit (value);
}
