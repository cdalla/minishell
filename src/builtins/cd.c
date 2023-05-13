/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 11:45:20 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/05/04 14:18:11 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*check if OLDPWD exist, add if not, update if exists*/
int	update_oldpwd(t_data *data, char *curr_wd, char *new_pwd)
{
	t_envp	*old_pwd;
	char	*old_path;
	char	*new_env_path;

	if (curr_wd)
		old_path = ft_strdup(curr_wd);
	else
		old_path = ft_strdup("");
	if (!old_path)
		return (free(new_pwd), print_err_msg(107, "cd"));
	old_pwd = var_exist(data->envp, "OLDPWD");
	if (old_pwd)
		update_var_value(data->envp, old_pwd, old_path, 0);
	else
	{
		new_env_path = ft_strjoin("OLDPWD=", old_path);
		if (!new_env_path || !add_env(&data->envp, new_env_path, 2))
			return (free(old_path), print_err_msg(107, "cd"));
		free(old_path);
		free(new_env_path);
	}
	return (0);
}

/*check if PWD exist, add if not, update if exists*/
int	update_pwd(t_data *data, char *new_pwd)
{
	t_envp	*pwd;
	char	*new_env_path;

	pwd = var_exist(data->envp, "PWD");
	if (pwd)
		update_var_value(data->envp, pwd, new_pwd, 0);
	else
	{
		new_env_path = ft_strjoin("PWD=", new_pwd);
		if (!new_env_path || !add_env(&data->envp, new_env_path, 2))
			return (print_err_msg(107, "cd"));
		free(new_env_path);
		free(new_pwd);
	}
	return (0);
}

/*save current wd, get new_path and change wd, update env*/
int	cd(t_scmd *arg, t_data *data)
{
	char	*cur_pwd;
	char	*new_pwd;
	char	*path;

	new_pwd = NULL;
	if (!arg)
	{
		path = get_env_value("HOME", data);
		if (!path)
			return (print_err_msg(111, "cd"));
	}
	else
		path = arg->value;
	cur_pwd = get_env_value("PWD", data);
	if (chdir(path) == -1)
		return (print_err_msg(errno, "cd"));
	new_pwd = getcwd(new_pwd, MAXPATHLEN);
	if (!new_pwd)
		return (print_err_msg(errno, "cd"));
	if (update_oldpwd(data, cur_pwd, new_pwd) || update_pwd(data, new_pwd))
		return (107);
	return (0);
}
