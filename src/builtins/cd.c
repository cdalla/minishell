/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 11:45:20 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/13 15:46:47 by cdalla-s      ########   odam.nl         */
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
			return (0); //malloc error
		}
	}
	free(cwd);
}

int	update_pwd(t_data *data, char *new_wd)
{
	t_envp	*new_pwd;
	
	new_pwd = var_exist(data->envp, "PWD");
	if (new_pwd)
		update_var_value(data->envp, new_pwd, new_wd, 0);
	else
	{
		if (!add_env(&data->envp, ft_strjoin("PWD=", new_wd), 2))
			return (0); //malloc error
	}
	free(new_wd);
	return (1);
}

char	*relative_path(char *path, char *cwd, t_data *data, char *new_wd)
{
	if (!path)
	{
		path = get_env_value("HOME", data);
		if (!path)
			printf("HOME not set!!!\n");
	}
	if (chdir(path) == -1)
		return (0);
	return (getcwd(new_wd, MAXPATHLEN));
}

char	*absolute_path(char *path, char *new_wd)
{
	if (chdir(path) == -1)
		return (0);
	return (getcwd(new_wd, MAXPATHLEN));
}

int	cd(t_scmd *args, t_data *data)
{
	char	*cwd = NULL;
	char	*new_wd = NULL;

	if (args->next_arg)
		printf("cd :syntax error");
	cwd = getcwd(cwd, MAXPATHLEN);
	if (!cwd)
		return (0);//error
	else
	{
		if (args->value[0] != '/')
			new_wd = relative_path(args->value, cwd, data, new_wd);
		else
			new_wd = absolute_path(args->value, new_wd);
	}
	if (!new_wd)
	{
		free(cwd);
		return (0);//error
	}
	if (!update_old(data, cwd, new_wd) || !update_pwd(data, new_wd))
		return (0);
	return (1);
}