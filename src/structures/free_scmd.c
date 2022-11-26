/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_scmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/25 14:11:11 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/26 14:09:11 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_infile(t_scmd *ptr)
{
	t_infile	*ptr_inf;
	t_infile	*next_inf;

	if (ptr->infile)
	{
		ptr_inf = ptr->infile;
		while (ptr_inf->next)
		{
			next_inf = ptr_inf->next;
			free(ptr_inf->filename);
			free(ptr_inf);
			ptr_inf = next_inf;
		}
	}
}

void	free_outfile(t_scmd *ptr)
{
	t_outfile	*ptr_out;
	t_outfile	*next_out;

	if (ptr->outfile)
	{
		ptr_out = ptr->outfile;
		while (ptr_out->next)
		{
			next_out = ptr_out->next;
			free(ptr_out->filename);
			free(ptr_out);
			ptr_out = next_out;
		}
	}
}

void	free_args(t_scmd *ptr)
{
	t_scmd	*ptr_arg;
	t_scmd	*next_arg;

	if (ptr->next_arg)
	{
		ptr_arg = ptr->next_arg;
		while (ptr_arg)
		{
			next_arg = ptr_arg->next_arg;
			free(ptr_arg->value);
			free(ptr_arg);
			ptr_arg = next_arg;
		}
	}
}

void	free_cmd(t_scmd *cmd)
{
	t_scmd	*ptr;
	t_scmd	*next_ptr;

	ptr = cmd;
	while (ptr)
	{
		next_ptr = ptr->next_cmd;
		if (ptr->cmd_name)
		{
			free(ptr->cmd_name->value);
			free(ptr->cmd_name);
		}
		free_args(ptr);
		free_infile(ptr);
		free_outfile(ptr);
		free(ptr);
		ptr = next_ptr;
	}
	cmd = 0;
}
