/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 11:37:50 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/13 11:44:41 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int pwd(t_scmd *args, t_data *data)
{
	char *path;
	
	if (args)
		printf("pwd: syntax error\n");
	else
		printf("%s\n", getcwd(path, MAXPATHLEN));
	return (1); //return errno
}