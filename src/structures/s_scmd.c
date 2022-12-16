/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   s_scmd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 12:09:10 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/16 13:26:05 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*create new SCMD node*/
t_scmd	*new_scmd(enum cmd_type type)
{
	t_scmd	*new_scmd;

	new_scmd = (t_scmd *)malloc(sizeof(t_scmd));
	if (!new_scmd)
		return (0); //failure
	new_scmd->type = type;
	new_scmd->cmd_name = 0;
	new_scmd->next_cmd = 0;
	new_scmd->next_arg = 0;
	new_scmd->prev_arg = 0;
	new_scmd->value = 0;
	new_scmd->infile = 0;
	new_scmd->outfile = 0;
	return (new_scmd);
}

/*append SCMD node to cmdlist*/
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

/*fill value field of SCMD*/
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

/*TO REMOVE*/
void	print_scmd(t_scmd *cmd)
{
	t_scmd		*ptr;
	t_infile	*inf;
	t_outfile	*out;
	int			i;

	i = 0;
	ptr = cmd;
	if (cmd->cmd_name)
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
			printf("infile %d = %s - type = %d\n", i, inf->filename, inf->type);
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
			printf("outfile %d = %s - type = %d\n", i, out->filename, out->type);
			i++;
			out = out->next;
		}
	}
}

/*TO REMOVE*/
void	print_multi_cmd(t_scmd *multi_cmd, int n_pipes)
{
	int		i;
	t_scmd	*ptr;

	i = 0;
	ptr = multi_cmd;
	while (ptr && i <= n_pipes)
	{
		printf("CMD %d\n", i + 1);
		print_scmd(ptr);
		i++;
		ptr = ptr->next_cmd;
	}
}
