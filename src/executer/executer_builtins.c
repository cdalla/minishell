/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer_builtins.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 09:59:26 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/13 10:19:35 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
	export, unset, env, pwd, cd, echo
*/
int	is_builtins(t_scmd *cmd, t_data *data, int i)
{
	if (!strncmp(cmd->cmd_name->value, "export", 7))
		export(cmd->next_arg, data);
	if (!strncmp(cmd->cmd_name->value, "unset", 6))
		unset();
	if (!strncmp(cmd->cmd_name->value, "env", 4))
		env();
	if (!strncmp(cmd->cmd_name->value, "pwd", 4))
		pwd();
	if (!strncmp(cmd->cmd_name->value, "cd", 3))
		cd();
	if (!strncmp(cmd->cmd_name->value, "echo", 5))
		echo();
	else
		return (0);
	return(1); //i need to return errorno
}
