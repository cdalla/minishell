/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 15:07:21 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/22 16:56:14 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	if (access(cmd_name, X_OK) == 0)
		return (cmd_name);
	else
	{
		join_cmd_name(cmd_name, paths);
		while (paths[i])
		{
			if (access(paths[i], X_OK) == 0)
				return (paths[i]);
			i++;
		}
	}
	return (0); //no path found
}

char **translate_list_env(t_envp *list, int type)
{
	t_envp	*ptr;
	int		size;
	char	**array;
	int		i;

	size = 0;
	i = 0;
	while (ptr)
	{
		size++;
		ptr = ptr->next;
	}
	array = (char **)malloc((size + 1) * sizeof(char *));
	if (!array)
		return (0); //malloc error
	ptr = list;
	while (ptr && i < size)
	{
		array[i] = 
	}
	return (array);
}

int	cmd_start(t_scmd *cmd, t_data *data)
{
	char	*cmd_path;
	
	// if (cmd->infile)
	// 	//set infiles
	// if (cmd->outfile)
	// 	//set outfile
	cmd_path = check_path_cmd(cmd->cmd_name->value, data);

	return (1);
}

int	executer_single(t_scmd *cmd, t_data *data)
{
	//no pipe
	pid_t	child;
	
	child = fork();
	if (child == 0)
	{
		//child task
		cmd_start(cmd, data);
	}
	else if (child > 0)
	{
		//parent wait the child end
		wait(NULL);
	}
	else
		return (0); //error
	return (1);
}

int	executer_multi(t_scmd **cmd_line, t_data *data, int n_pipes)
{
	int	i;

	i = 0;
	while (i <= n_pipes)
	{
		//set fd for pipes
		executer_single(cmd_line[i], data);
		//check execution return
	}
	return (1);// success
}
