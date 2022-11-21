/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   s_scmd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 12:09:10 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/21 16:45:13 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_scmd	*new_scmd(enum cmd_type type)
{
	t_scmd	*new_scmd;

	new_scmd = (t_scmd *)malloc(sizeof(t_scmd));
	if (!new_scmd)
		return (0); //failure
	new_scmd->type = type;
	new_scmd->next_arg = 0;
	new_scmd->prev_arg = 0;
	new_scmd->value = 0;
	new_scmd->infile = 0;
	new_scmd->outfile = 0;
	return (new_scmd);	
}

int	add_scmd_arg(t_scmd *cmd, t_scmd *arg)
{
	t_scmd	*ptr;
	
	if (!cmd || !arg)
		return (0); //error
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
			arg->prev_arg = ptr;
		}
	}
	return (1); //succes
}

int	set_scmd_value(t_scmd *cmd, char *value)
{
	if (!value)
		cmd->value = NULL;
	else
	{
		cmd->value = ft_strdup(value);
		if (!cmd->value)
			return (0); //strdup error
	}
	return (1); //success
}

void print_scmd(t_scmd *cmd)
{
	t_scmd *ptr;
	t_infile *inf;
	t_outfile *out;
	int i = 1;

	ptr = cmd;
	printf("cmd name = %s\n", ptr->cmd_name->value);
	ptr = ptr->next_arg;
	while (ptr)
	{
		printf("arg %d = %s\n", i, ptr->value);
		i++;
		ptr = ptr->next_arg;
	}
	ptr = cmd;
	if (ptr->infile)
	{
		inf = ptr->infile;
		i = 1;
		while (inf)
		{
			printf("infile %d = %s\n", i, inf->filename);
			i++;
			inf = inf->next;
		}
	}
		if (ptr->outfile)
	{
		out = ptr->outfile;
		i = 1;
		while (out)
		{
			printf("outfile %d = %s\n", i, out->filename);
			i++;
			out = out->next;
		}
	}
}