/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 11:37:50 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/04/29 13:08:07 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*print current working directory*/
int	pwd(t_scmd *args, t_data *data)
{
	char	*path;

	path = NULL;
	(void)data;
	(void)args;
	printf("%s\n", getcwd(path, MAXPATHLEN));
	return (0);
}
