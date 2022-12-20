/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer_builtins.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 09:59:26 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/20 16:12:08 by cdalla-s      ########   odam.nl         */
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
	char	*builtin_name;
	int		(*fn)(t_scmd *, t_data *);
}				t_builtin;

int	execute_builtin(int	(*fn)(t_scmd *, t_data *), t_scmd *cmd, t_data *data)
{	
	if (data->to_close != -1)
		close(data->to_close);
	if (!set_red(cmd->file, data))
		printf("redirection error\n");
	fn(cmd->next_arg, data);// check return of builtin execution
	return (1);
}

/*check if this is a bultin and call the corresponding function*/
int	is_builtins(t_scmd *cmd, t_data *data, int i)
{
	int			index;
	char		*name;
	const t_builtin	builtin[6] = {{"echo", &echo}, {"env", &env}, {"cd", &cd},
	{"export", &export}, {"unset", &unset}, {"pwd", &pwd}};

	index = 0;
	(void)i;
	name = cmd->cmd_name->value;
	while (index < 6)
	{
		if (!ft_strncmp(name, builtin[index].builtin_name, ft_strlen(name) + 1))
		{	
			execute_builtin(builtin[index].fn, cmd, data);
			return(1);
		}
		index++;
	}
	return(0);
}
