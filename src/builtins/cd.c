/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 11:45:20 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/13 11:48:18 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd(t_scmd *args, t_data *data)
{
	if (args->next)
		printf("cd :syntax error");
	else
	{
		
	}
}