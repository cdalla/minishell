/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_print.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/30 11:39:06 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/30 12:38:01 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*err_msg(int err_num)
{
	if (err_num == 107)
		return ("minshell: malloc error");
	else if (err_num == 108)
		return ("minishell: syntax error");
	else
		return ("minishell: msg not found");
}

void	print_error(int err_num)
{
	if (errno)
		printf("minishell: errno %d = %s\n", errno, strerror(errno));
	else
		printf("minishell: error: %s\n", err_msg(err_num));
}