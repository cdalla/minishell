/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_print.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/30 11:39:06 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/03 15:44:46 by cdalla-s      ########   odam.nl         */
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

/*add a str for the word, file, cmd who failed*/
int	print_err_msg(int exit_code, char *str)
{
	if (exit_code)
	{
		if (exit_code < 107)
		{
			write(2, "minishell: ", 12);
			write(2, str, ft_strlen(str));
			write(2, ": ", 2);
			write(2, strerror(exit_code), ft_strlen(strerror(exit_code)));
			write(2, "\n", 1);
		}
		else
		{
			write(2, "minishell: ", 12);
			write(2, str, ft_strlen(str));
			write(2, ": ", 2);
			write(2, err_msg(exit_code), ft_strlen(err_msg(exit_code)));
			write(2, "\n", 1);
		}
	}
	return (exit_code);
}
