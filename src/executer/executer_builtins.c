/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer_builtins.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 09:59:26 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/16 13:36:51 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
	export, unset, env, pwd, cd, echo
*/

int	echo(t_scmd *args, t_data *data);
int	cd(t_scmd *args, t_data *data);
int	env(t_scmd *args, t_data *data);
int	export(t_scmd *args, t_data *data);
int pwd(t_scmd *args, t_data *data);
int	unset(t_scmd *args, t_data *data);


/*check if this is a bultin and call the corresponding function*/
int	is_builtins(t_scmd *cmd, t_data *data, int i)
{
	(void)i;
	if (!ft_strncmp(cmd->cmd_name->value, "export", 7))
		export(cmd->next_arg, data);
	else if (!ft_strncmp(cmd->cmd_name->value, "unset", 6))
		unset(cmd->next_arg, data);
	else if (!ft_strncmp(cmd->cmd_name->value, "env", 4))
		env(cmd->next_arg, data);
	else if (!ft_strncmp(cmd->cmd_name->value, "pwd", 4))
		pwd(cmd->next_arg, data);
	else if (!ft_strncmp(cmd->cmd_name->value, "cd", 3))
		cd(cmd->next_arg, data);
	else if (!ft_strncmp(cmd->cmd_name->value, "echo", 5))
		echo(cmd->next_arg, data);
	else
	{
		//printf("builtin not found\n");
		return (0);
	}
	return(1); //i need to return errorno
}
