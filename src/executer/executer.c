/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 15:07:21 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/05/03 10:55:52 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		loop_multi_cmd(t_data *data, t_scmd *cmd, int i);
int		executer_single(t_scmd *cmd, t_data *data);
int		heredoc(t_scmd *cmd);
int		destroy_heredoc(t_scmd *cmd);

/*wait exit status of last process*/
int	wait_function(pid_t child, t_data *data)
{
	int	status;
	int	exit_child;

	exit_child = -1;
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		exit_child = (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		exit_child = WTERMSIG(status) + 128;
	if (exit_child == 131)
		write(2, "Quit: 3\n", 9);
	while (data->n_pipes > 0)
	{
		wait(NULL);
		data->n_pipes--;
	}
	return (exit_child);
}

/*if n_pipes present call multi command, otherwise single*/
int	executer(t_scmd *cmd, t_data *data)
{
	int		ret;
	t_scmd	*ptr;

	data->cmd_path = 0;
	data->envp_ar = 0;
	data->cmd_args = 0;
	ptr = cmd;
	ret = heredoc(ptr);
	if (data->n_pipes && !ret)
		ret = loop_multi_cmd(data, cmd, 0);
	else if (!ret)
		ret = executer_single(cmd, data);
	destroy_heredoc(ptr);
	return (ret);
}
