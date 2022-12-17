/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   s_redirection.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 11:38:32 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/17 22:34:54 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*create new infile node*/
// t_infile	*new_infile(enum red_type type, char *value)
// {
// 	t_infile	*new_inf;

// 	new_inf = (t_infile *)malloc(sizeof(t_infile));
// 	if (!new_inf)
// 		return (0); //malloc failed
// 	new_inf->type = type;
// 	new_inf->next = 0;
// 	new_inf->filename = ft_strdup(value);
// 	if (!new_inf->filename)
// 		return (0); //failed in strdup
// 	return (new_inf);
// }

/*add infile node to infile list*/
// int	add_infile(t_scmd *cmd, enum red_type type, char *value)
// {
// 	t_infile	*new;
// 	t_infile	*ptr;

// 	if (!cmd || !type || !value)
// 		return (0);
// 	new = new_infile(type, value);
// 	if (!new)
// 		return (0); //failed in node creation
// 	if (!cmd->infile)
// 		cmd->infile = new;
// 	else
// 	{
// 		ptr = cmd->infile;
// 		while (ptr->next)
// 			ptr = ptr->next;
// 		ptr->next = new;
// 	}
// 	return (1); //success
// }

/*create new outfile node*/
// t_outfile	*new_outfile(enum red_type type, char *value)
// {
// 	t_outfile	*new_outf;

// 	new_outf = (t_outfile *)malloc(sizeof(t_outfile));
// 	if (!new_outf)
// 		return (0); //malloc failed
// 	new_outf->type = type;
// 	new_outf->next = 0;
// 	new_outf->filename = ft_strdup(value);
// 	if (!new_outf->filename)
// 		return (0); //failed in strdup
// 	return (new_outf);
// }

/*add outfile node to outfile list*/
// int	add_outfile(t_scmd *cmd, enum red_type type, char *value)
// {
// 	t_outfile	*new;
// 	t_outfile	*ptr;

// 	if (!cmd || !type || !value)
// 		return (0);
// 	new = new_outfile(type, value);
// 	if (!new)
// 		return (0); //failed in node creation
// 	if (!cmd->outfile)
// 		cmd->outfile = new;
// 	else
// 	{
// 		ptr = cmd->outfile;
// 		while (ptr->next)
// 			ptr = ptr->next;
// 		ptr->next = new;
// 	}
// 	return (1); //success
// }

t_file	*new_file(enum token_type type, char *value)
{
	t_file	*new_file;

	new_file = (t_file *)malloc(sizeof(t_file));
	if (!new_file)
		return (0); //malloc failed
	new_file->type = type;
	new_file->next = 0;
	new_file->filename = ft_strdup(value);
	if (!new_file->filename)
		return (0); //failed in strdup
	return (new_file);
}

int	add_file(t_scmd *cmd, enum token_type type, char *value)
{
	t_file	*new;
	t_file	*ptr;

	if (!cmd || !type || !value)
		return (0);
	new = new_file(type, value);
	if (!new)
		return (0); //failed in node creation
	if (!cmd->file)
		cmd->file = new;
	else
	{
		ptr = cmd->file;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	return (1); //success
}
