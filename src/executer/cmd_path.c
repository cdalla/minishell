/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/25 12:50:15 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/20 16:44:04 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*str_split %PATH*/
char	**split_paths(t_envp *envp)
{
	char	*path;
	char	**split_path;
	t_envp	*ptr;

	ptr = envp;
	while (ft_strncmp(ptr->env, "PATH", 5) && ptr)
		ptr = ptr->next;
	if (!ptr)
		return (0); //$PATH has been deleted
	path = ft_strdup(ptr->value);
	if (!path)
		return (0); //malloc fail
	split_path = ft_split(path, ':');
	free(path);
	if (!split_path)
		return (0); //malloc fail
	return (split_path);
}

/*str_join directory path with cmd_name*/
int	join_cmd_name(char *cmd_name, char **paths)
{
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (0); //error and free
		free(paths[i]);
		paths[i] = ft_strjoin(tmp, cmd_name);
		if (!paths[i])
			return (0);// error and free all path
		free(tmp);
		i++;
	}
	return (1);
}

/*split $PATH, join with cmd_name, check CMD presence*/
char	*check_path_cmd(char *cmd_name, t_data *data)
{
	char	**paths;
	//char	*cmd_path;
	int		i;

	i = 0;
	paths = split_paths(data->envp);
	if (!paths)
		return (0);//error in split_paths nothing to free
	join_cmd_name(cmd_name, paths); // if this fail return zero and free path
	while (paths[i])
	{
		if (access(paths[i], F_OK) == 0)
			return (paths[i]);
		i++;
	}
	// if (access(cmd_name, F_OK) == 0)
		return (cmd_name);
	//return (0); //no path found
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