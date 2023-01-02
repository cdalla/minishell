/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 11:45:20 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/02 17:07:00 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	-save always the current directory path

	if (path[0]!='/')
	-relative path -> check with access if the folder is present
		(0 for success)(mode F_OK)-> strjoin to pwd and open with chdir
	else
	-absolute path check if chdir works

	-".." trim last part of the current path and open it with chdir
	- no args open $HOME

	if SUCCESS:

	-change PWD with the new path
	-save initial path in OLDPWD, add OLDPWD if it does not exist
*/

/*check if OLDPWD exist, add if not, update if exists*/
int	update_old(t_data *data, char *cwd, char *new_wd)
{
	t_envp	*old_pwd;

	old_pwd = var_exist(data->envp, "OLDPWD");
	if (old_pwd)
		update_var_value(data->envp, old_pwd, cwd, 0);
	else
	{
		if (!add_env(&data->envp, ft_strjoin("OLDPWD=", cwd), 2))
		{
			free(cwd);
			free(new_wd);
			return (print_err_msg(107)); //malloc error
		}
	}
	//free(cwd);
	return(0);
}

/*check if PWD var exist, add if not, update if exists*/
int	update_pwd(t_data *data, char *new_wd)
{
	t_envp	*new_pwd;
	
	new_pwd = var_exist(data->envp, "PWD");
	if (new_pwd)
		update_var_value(data->envp, new_pwd, new_wd, 0);
	else
	{
		printf("add new PWD VAR");
		if (!add_env(&data->envp, ft_strjoin("PWD=", new_wd), 2))
		{
			free(new_wd);
			return (print_err_msg(107)); //malloc error
		}
	}
	return (0);
}

/*change wd, if no arg $HOME is used*/
char	*change_dir(t_scmd *arg, t_data *data, char *new_wd)
{
	char	*path;

	if (!arg)//no arguments open $HOME
	{
		path = get_env_value("HOME", data);
		if (!path)
			printf("HOME not set!!!\n");
	}
	else
		path = arg->value;
	if (chdir(path) == -1)
		return (0); //errno
	return (getcwd(new_wd, MAXPATHLEN));
}

/*save current wd, get new_path and change wd, update env*/
int	cd(t_scmd *args, t_data *data)
{
	char	*cwd = NULL;
	char	*new_wd = NULL;
	int		ret;

	cwd = getcwd(cwd, MAXPATHLEN);
	if (!cwd)
		return (print_err_msg(errno));//error
	new_wd = change_dir(args, data, new_wd);
	if (!new_wd)
	{
		free(cwd);
		return (print_err_msg(errno));//error
	}
	ret = update_old(data, cwd, new_wd);
	if (ret)
		return (ret);
	ret = update_pwd(data, new_wd);
	if (ret)
		return (ret);
	return (0);
}