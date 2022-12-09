/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_var.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 12:39:13 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/09 13:17:00 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	need double pointer to modify token list head
	check syntax <key>=<value>
	!check if there is a = sign not in first position
	if shell var already exist update value
	!only letters and numbers allowed in var name
	!var name cannot start with a number

	try to add a var with no value
*/
int	check_var_syntax(char *str)
{
	int		i;

	i = 0;
	if (!ft_isalpha(str[0]))
		return (0);
	while(str[i])
	{	
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]))
			return (0);
		if (str[i] == '=' && i > 0)
			return (1);
	}
	return (0);
}

//check if is a var
//check if var exist -> update value -> remove token
//add new shell var -> remove token
int	check_shell_var(t_token *token)
{
	t_token	*ptr;

	ptr = token;
	if (!check_var_syntax(ptr->word))
		return (1); //just want to not add a variable but not to stop the program
	
}