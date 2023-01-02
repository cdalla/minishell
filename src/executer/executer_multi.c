/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer_multi.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/22 12:38:41 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/02 16:29:50 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		wait_function(pid_t child, int i, t_data *data);
int		execve_param(t_scmd *cmd, t_data *data);
int		parent_close(int fd[2][2], int i, int n_pipes);
void	free_execve_param(t_data *data);
void	set_fd(t_data *data, int fd[2][2], int i);

/*check if execute builtin or call execve in child*/
int	child_process_multi(t_scmd *cmd, t_data *data)
{
	int	ret;
	if ((data->to_close != -1))
	{
		if(close(data->to_close) == -1)
			exit(print_err_msg(errno));
	}
	if (is_builtin(cmd))
	{
		exit(execute_builtin(cmd, data));
	}
	else
	{
		ret = set_red(cmd->file, data);
		if (ret)
			exit(ret);//open or close error or dup2
		execve(data->cmd_path, data->cmd_args, data->envp_ar);
	}
	exit(ret);
}

/*fork a child need to execute builtin inside*/
int	exec_in_child_multi(t_scmd *cmd, t_data *data, int i)//need to call builtins here
{
	pid_t	child;
	int		ret;

	ret = 0;
	child = fork();
	if (child == 0) //child
	{
		//signals_child();
		ret = child_process_multi(cmd, data);
		// if (!child_process_multi(cmd, data))
		// 	exit(0);//i dont know if it returns
		// exit(0);
	}
	else if (child > 0) //parent
	{
		ret = wait_function(child, i, data);
	}
	else if (child < 0)
		return (errno); //error fork
	return (ret);
}

/*set pipes, set fd, call execution of every command, close fd*/
int	executer_multi(t_scmd *cmd, t_data *data, int i)
{
	int		fd[2][2];
	int		ret;
	int		ret2;

	if (i < data->n_pipes)
	{
		if (pipe(fd[i % 2]) == -1)
			return (print_err_msg(errno)); //pipe eror
	}
	set_fd(data, fd, i);
	if (!is_builtin(cmd))
	{
		if (!execve_param(cmd, data))
			return (0); //set errno and return FAILURE
	}
	ret = exec_in_child_multi(cmd, data, i);//executer return 0 for error and errno will be set and close
	if (!is_builtin(cmd))
		free_execve_param(data);
	ret2 = parent_close(fd, i, data->n_pipes);
	if (ret2)
		return (ret2);
	return (ret);// success
}
