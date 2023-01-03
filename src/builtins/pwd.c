/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 11:37:50 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/03 15:39:30 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*print current working directory*/
int	pwd(t_scmd *args, t_data *data)
{
	char	*path;

	path = NULL;
	(void)data;
	if (args)
		return (print_err_msg(108, "pwd"));
	else
		printf("%s\n", getcwd(path, MAXPATHLEN));
	return (0);
}
