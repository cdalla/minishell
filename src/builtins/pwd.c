/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 11:37:50 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/05/03 11:45:38 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*print current working directory*/
int	pwd(t_scmd *args, t_data *data)
{
	char	*path;
	char	*ret;

	path = NULL;
	(void)data;
	(void)args;
	ret = getcwd(path, MAXPATHLEN);
	if (!ret)
		return (print_err_msg(errno, "pwd"));
	printf("%s\n", ret);
	free(ret);
	return (0);
}
