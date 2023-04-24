/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/15 12:53:06 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/04/24 14:34:44 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*check if the arg is a flag or a printable str*/
int	is_printable(char *str, int *flag)
{
	int	i;

	i = 0;
	if (str[0] == '-')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (1);
			i++;
		}
		*flag = 1;
		return (0);
	}
	return (1);
}

/*call flag check, print the args*/
int	echo(t_scmd *args, t_data *data)
{
	int		flag;
	int		printed;
	t_scmd	*ptr;

	(void)data;
	flag = 0;
	printed = 0;
	ptr = args;
	while (ptr)
	{
		if (is_printable(ptr->value, &flag))
		{
			if (ptr != args && printed)
				write(STDOUT_FILENO, " ", 1);
			write(STDOUT_FILENO, ptr->value, ft_strlen(ptr->value));
			printed = 1;
		}
		ptr = ptr->next_arg;
	}
	if (!flag)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
