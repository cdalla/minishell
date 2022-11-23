#include "../minishell.h"

char **split_paths(t_envp *envp)
{
	char	*path;
	t_envp	*ptr;

	ptr = envp;
	while (ft_strncmp(ptr->env, "PATH", 5) && ptr)
		ptr = ptr->next;
	if (!ptr)
		return (0);
	path = ft_strdup(ptr->value);
	if (!path)
		return (0);
	return (ft_split(path, ':'));
}

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
			return (0);// error and free
		free(tmp);
		i++;
	}
	return (1);
}

char *check_path_cmd(char *cmd_name, t_data *data)
{
	char	**paths;
	int		i;
	
	i = 0;
	paths = split_paths(data->envp);
	if (!paths)
		return (0);//error in split
	join_cmd_name(cmd_name, paths);
	while (paths[i])
	{
		if (access(paths[i], F_OK) == 0)
			return (paths[i]);
		i++;
	}
	if (access(cmd_name, F_OK) == 0)
		return (cmd_name);
	return (0); //no path found
}
