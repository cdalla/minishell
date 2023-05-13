/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   s_scmd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 12:09:10 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/04/25 16:01:57 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*create new SCMD node*/
t_scmd	*new_scmd(enum e_cmd_type type)
{
	t_scmd	*new_scmd;

	new_scmd = (t_scmd *)malloc(sizeof(t_scmd));
	if (!new_scmd)
		return (0);
	new_scmd->type = type;
	new_scmd->cmd_name = 0;
	new_scmd->next_cmd = 0;
	new_scmd->next_arg = 0;
	new_scmd->value = 0;
	new_scmd->file = 0;
	return (new_scmd);
}

/*append SCMD node to cmdlist*/
int	add_scmd_arg(t_scmd *cmd, t_scmd *arg)
{
	t_scmd	*ptr;

	if (!cmd || !arg)
		return (0);
	if (!cmd->cmd_name)
		cmd->cmd_name = arg;
	else
	{
		if (!cmd->next_arg)
			cmd->next_arg = arg;
		else
		{
			ptr = cmd->next_arg;
			while (ptr->next_arg)
				ptr = ptr->next_arg;
			ptr->next_arg = arg;
		}
	}
	return (1);
}

/*fill value field of SCMD*/
int	set_scmd_value(t_scmd *cmd, char *value)
{
	if (!value)
		cmd->value = NULL;
	else
	{
		cmd->value = ft_strdup(value);
		if (!cmd->value)
			return (0);
	}
	return (1);
}
