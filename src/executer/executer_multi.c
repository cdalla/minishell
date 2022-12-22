/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer_multi.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/22 12:38:41 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/22 14:50:30 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		wait_function(pid_t child, int i, t_data *data);
int		execve_param(t_scmd *cmd, t_data *data);
void	free_execve_param(t_data *data);
void	set_fd(t_data *data, int fd[2][2], int i);
void	parent_close(int fd[2][2], int i, int n_pipes);

/*check if execute builtin or call execve in child*/
int	child_process_multi(t_scmd *cmd, t_data *data)
{
	if ((data->to_close != -1))
	{
		if(close(data->to_close) == -1)
		{
			printf("close error in child multi\n");
			return (0);
		}
	}
	if (is_builtin(cmd))
	{
		if (!execute_builtin(cmd, data))
		{
			printf("error execute builtin in multi\n");
			return (0);
		}
	}
	else
	{
		if (!set_red(cmd->file, data))
		{
			printf("%s execve redirection error\n", cmd->cmd_name->value);
			return(0);//open or close error
		}
		execve(data->cmd_path, data->cmd_args, data->envp_ar);
	}
	return (1);
}

/*fork a child need to execute builtin inside*/
int	exec_in_child_multi(t_scmd *cmd, t_data *data, int i)//need to call builtins here
{
	pid_t	child;

	child = fork();
	if (child == 0) //child
	{
		if (!child_process_multi(cmd, data))
			exit(0);//i dont know if it returns
		exit(0);
	}
	else if (child > 0) //parent
	{
		if (!wait_function(child, i, data))
			return (0);
	}
	else if (child < 0)
		return (0); //error
	return (1);
}

/*set pipes, set fd, call execution of every command, close fd*/
int	executer_multi(t_scmd *cmd, t_data *data, int i)
{
	int		fd[2][2];
	int		ret;

	if (i < data->n_pipes)
	{
		if (pipe(fd[i % 2]) == -1)
		{
			printf("pipe error\n");
			return (0); //pipe error
		}
	}
	set_fd(data, fd, i);
	//printf("after set fd %, read %d, ");
	if (!is_builtin(cmd))
	{
		if (!execve_param(cmd, data))
			return (0); //set errno and return FAILURE
	}
	ret = exec_in_child_multi(cmd, data, i);//executer return 0 for error and errno will be set and close
	if (!is_builtin(cmd))
		free_execve_param(data);
	parent_close(fd, i, data->n_pipes);
	return (ret);// success
}
