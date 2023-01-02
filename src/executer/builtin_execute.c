/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_execute.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 09:59:26 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/02 16:34:39 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
	export, unset, env, pwd, cd, echo
*/

int	echo(t_scmd *args, t_data *data);
int	cd(t_scmd *args, t_data *data);
int	env( t_scmd *args, t_data *data);
int	export(t_scmd *args, t_data *data);
int pwd(t_scmd *args, t_data *data);
int	unset(t_scmd *args, t_data *data);

typedef struct s_builtin
{
	char	*name;
	int		(*fn)(t_scmd *, t_data *);
}				t_builtin;

int	execute_builtin(t_scmd *cmd, t_data *data)
{	
	int			i;
	int			ret;
	char		*name;
	const t_builtin	builtin[6] = {{"echo", &echo}, {"env", &env}, {"cd", &cd},
	{"export", &export}, {"unset", &unset}, {"pwd", &pwd}};
	
	i = 0;
	name = cmd->cmd_name->value;
	if (data->to_close != -1)
		close(data->to_close);
	ret = set_red(cmd->file, data);
	if (ret)
		return (ret);
	while (i < 6)
	{
		if (!ft_strncmp(name, builtin[i].name, ft_strlen(name) + 1))
			return(builtin[i].fn(cmd->next_arg, data));// check return of builtin execution
		i++;
	}
	return (0); //set command not found
}

/*check if this is a bultin and call the corresponding function*/
int	is_builtin(t_scmd *cmd)
{
	int			index;
	char		*name;
	const char	*builtin[6] = {"echo", "env", "cd", "export", "unset", "pwd"};

	index = 0;
	if (cmd->cmd_name)
		name = cmd->cmd_name->value;
	else
		return (0); // return code is to not execute
	while (index < 6)
	{
		if (!ft_strncmp(name, builtin[index], ft_strlen(name) + 1))
			return (1);
		index++;
	}
	return(0);
}
