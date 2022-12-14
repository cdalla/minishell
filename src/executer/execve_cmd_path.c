/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve_cmd_path.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/25 12:50:15 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/08 14:42:15 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*str_split %PATH*/
char	**split_paths(t_data *data)
{
	char	*path;
	char	**split_path;

	if (!get_env_value("PATH", data))
		return (0);
	path = ft_strdup(get_env_value("PATH", data));
	if (!path)
		return (0);
	split_path = ft_split(path, ':');
	free(path);
	if (!split_path)
		return (0);
	return (split_path);
}

/*str_join directory path with cmd_name*/
char	*join_cmd_name(char *cmd_name, char **paths)
{
	char	*tmp;
	char	*cmd_path;
	int		i;

	i = 0;
	cmd_path = 0;
	tmp = ft_strjoin("/", cmd_name);
	if (!tmp)
		return (0);
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], tmp);
		if (!cmd_path)
			break ;
		if (access(cmd_path, F_OK) == 0)
			break ;
		free(cmd_path);
		cmd_path = 0;
		i++;
	}
	if (!paths[i])
		cmd_path = ft_strdup(cmd_name);
	free(tmp);
	return (cmd_path);
}

/*split $PATH, join with cmd_name, check CMD presence*/
//check first if path exist and otherwise return cmd_name
char	*check_path_cmd(char *cmd_name, t_data *data)
{
	char	**paths;
	char	*cmd_path;
	int		i;

	i = 0;
	paths = split_paths(data);
	if (!paths)
	{
			return (0);
		// cmd_path = ft_strdup(cmd_name);
		// return (cmd_path);
	}
	cmd_path = join_cmd_name(cmd_name, paths);
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	if (!cmd_path)
		return (0);
	return (cmd_path);
}

void	print_dsarry(char **array)//just for testing purpose !!!REMOVE!!!
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}
