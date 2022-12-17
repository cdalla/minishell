/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/15 12:53:06 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/17 16:26:52 by cdalla-s      ########   odam.nl         */
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
		while(str[i])
		{
			if (str[i] != 'n')
				return (1);
			i++;
		}
		*flag = 1;
		return(0);
	}
	return(1);
}

/*call flag check, print the args*/
int	echo(t_scmd *args, t_data *data)
{
	int		flag;
	t_scmd	*ptr;

	flag = 0;
	(void)data;
	ptr = args;
	while (ptr)
	{
		if (is_printable(ptr->value, &flag))
		{
			if (ptr != args)
				printf(" ");
			printf("%s", ptr->value);
		}
		ptr = ptr->next_arg;
	}
	if (!flag)
		printf("\n");
	return (1); //maybe return errno
}

// int	echo(t_scmd *args, t_data *data)
// {
// 	int		flag;
// 	t_scmd	*ptr;

// 	printf("in echo\n");
// 	flag = 0;
// 	(void)data;
// 	ptr = args;
// 	while (ptr)
// 	{
// 		if (is_printable(ptr->value, &flag))
// 		{
// 			// if (ptr != args)
// 			// 	printf(" ");
// 			//printf("%s", ptr->value);
// 			ft_putstr_fd(ptr->value, STDOUT_FILENO);
// 		}
// 		ptr = ptr->next_arg;
// 	}
// 	if (!flag)
// 		ft_putstr_fd("\n", STDOUT_FILENO);
// 	// 	printf("\n");
// 	// 	ft_putendl_fd()
// 	return (1); //maybe return errno
//}