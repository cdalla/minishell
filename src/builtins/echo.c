/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/15 12:53:06 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/15 13:03:01 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_printable(char *str, int *flag)
{
	int	i;

	i = 0;
	if (str[0] == '-')
	{
		i++;
		while(str[i])
		{
			if (str[i] != 'n')
				return (1);
			i++;
		}
	}
	*flag = 1;
	return(0);
}

int	echo(t_scmd *args, t_data *data)
{
	int		flag;
	t_scmd	*ptr;

	flag = 0;
	while (ptr)
	{
		if (is_printable(ptr->value, &flag))
			printf("%s", ptr->value);
		ptr = ptr->next_arg;
	}
	if (!flag)
		printf("\n");
	return (1); //maybe return errno
}