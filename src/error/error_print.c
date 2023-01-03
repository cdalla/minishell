/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_print.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/30 11:39:06 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/03 11:54:26 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*err_msg(int err_num)
{
	if (err_num == 107)
		return ("malloc error");
	else if (err_num == 108)
		return ("syntax error");
	else if (err_num == 109)
		return ("too many args");
	else if (err_num == 127)
		return ("command not found");
	else if (err_num == 126)
		return ("command not executable");
	else
		return ("error msg not found");
}

void	print_error(int err_num)
{
	if (errno)
		printf("minishell: errno %d = %s\n", errno, strerror(errno));
	else
		printf("minishell: error: %s\n", err_msg(err_num));
}


/*add a str for the word, file, cmd who failed*/
int	print_err_msg(int exit_code, char *str)
{
	if (exit_code)
	{
		if (exit_code < 107)
			printf("minishell: %s: %s\n", str, strerror(exit_code));
		else
			printf("minishell: %s: %s\n", str, err_msg(exit_code));
	}
	return (exit_code);
}