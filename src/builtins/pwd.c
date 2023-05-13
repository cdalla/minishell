/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 11:37:50 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/05/04 12:37:53 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*print current working directory*/
int	pwd(t_scmd *args, t_data *data)
{
	char	*path;
	char	*ret_get;
	char	*ret_env;

	path = NULL;
	(void)args;
	ret_get = getcwd(path, MAXPATHLEN);
	if (!ret_get)
	{
		ret_env = get_env_value("PWD", data);
		if (!ret_env)
			return (print_err_msg(errno, "pwd"));
		printf("%s\n", ret_env);
		return (0);
	}
	printf("%s\n", ret_get);
	free(ret_get);
	return (0);
}
