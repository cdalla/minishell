/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 15:07:21 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/05/02 17:26:37 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		executer_multi(t_scmd *cmd, t_data *data, int i);
int		executer_single(t_scmd *cmd, t_data *data);
int		heredoc(t_scmd *cmd);
int		destroy_heredoc(t_scmd *cmd);

/*wait exit status of last process*/
int	wait_function(pid_t child, int i, t_data *data)
{
	int	exit_child;

	exit_child = 0;
	if (i == data->n_pipes)
	{
		waitpid(child, &exit_child, 0);
		// while (i > 0)
		// {
		// 	i--;
		// 	waitpid(child, NULL, 0);
		// }
		while (wait(NULL) > 0)
			continue ;
		if (exit_child == 2)
			return (130);
		else if (exit_child == 3)
		{
			write(2, "Quit: 3\n", 9);
			return (131);
		}
		else if (exit_child != 0)
			return (exit_child / 256);
	}
	return (exit_child);
}

/*loop cmd and call execution*/
int	loop_multi_cmd(t_data *data, t_scmd *cmd)
{
	int	i;
	int	ret;
	
	i = 0;
	ret = 0;
	while (cmd)
	{
		ret = executer_multi(cmd, data, i);
		if (ret)
			break ;
		cmd = cmd->next_cmd;
		i++;
	}
	ret = wait_function(data->child, i, data);
	return (ret);
}

/*if n_pipes present call multi command, otherwise single*/
int	executer(t_scmd *cmd, t_data *data)
{
	int		ret;
	t_scmd	*ptr;

	ret = 0;
	data->cmd_path = 0;
	data->envp_ar = 0;
	data->cmd_args = 0;
	ptr = cmd;
	ret = heredoc(ptr);
	if (data->n_pipes && !ret)
		ret = loop_multi_cmd(data, cmd);
	else if (!ret)
		ret = executer_single(cmd, data);
	destroy_heredoc(ptr);
	return (ret);
}
