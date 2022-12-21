/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 15:07:21 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/21 13:53:54 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_fd(t_data *data, int fd[2][2], int i);
void	parent_close(int fd[2][2], int i, int n_pipes);
int 	save_std_fd(int *in, int *out);
int		reset_std_fd(int in, int out);

/*translate necessary list in array[], set red, execve with right info*/
int	cmd_start(t_scmd *cmd, t_data *data)//probable leak in the 3 function malloced, path
{
	char	*cmd_path;
	char	**envp_ar;
	char	**cmd_args;

	if ((data->to_close != -1))
	{
		if(close(data->to_close) == -1)
		{
			printf("close error in child\n");
			exit (0);
		}
	}
	if (!set_red(cmd->file, data))
	{	
		printf("redirection child error\n");
		exit(0);//open or close error
	}
	cmd_path = check_path_cmd(cmd->cmd_name->value, data);
	if (!cmd_path)
	{
		printf("cmd path error\n");
		exit (0); //malloc error
	}
	envp_ar = ls_toarr_env(data->envp);
	if (!envp_ar)
	{
		printf("envp array error\n");
		exit (0); //malloc error
	}
	cmd_args = ls_toarr_args(cmd->next_arg, cmd_path);
	if (!cmd_args)
	{
		printf("cmd args array error\n");
		exit (0); //malloc error
	}
	printf("execve return = %d\n", execve(cmd_path, cmd_args, envp_ar));
	//execve(check_path_cmd, ls_toarr_env, ls_toarr_args); //this is nice :) do not care about ret
	return (0);
}

/*set redirection, call execve*/
int	child_process_single(t_scmd *cmd, t_data *data)
{
	if ((data->to_close != -1))
	{
		if(close(data->to_close) == -1)
			exit (0);
	}
	if (!set_red(cmd->file, data))
		exit(0);//open or close error
	execve(data->cmd_path, data->cmd_args, data->envp_ar);
}

/*check if execute builtin or call execve in child*/
int	child_process_multi(t_scmd *cmd, t_data *data)
{
	if ((data->to_close != -1))
	{
		if(close(data->to_close) == -1)
			exit (0);
	}
	if (is_builtin(cmd))
		execute_builtin(cmd, data);
	else
	{
		if (!set_red(cmd->file, data))
			exit(0);//open or close error
		execve(data->cmd_path, data->cmd_args, data->envp_ar);
	}
}

/*wait exit status of last process*/
int	wait_function(pid_t child, int i, t_data *data)
{
	if (i == data->n_pipes)
	{
		waitpid(child, &status, 0);
		if (status != 0)
		{
			printf("execve error process i = %d\n", i);
			return (0);
		}
	}
	return (1);
}

/*fork a child process, call execution of single cmd*/
int	exec_in_child_single(t_scmd *cmd, t_data *data)
{
	pid_t	child;

	child = fork();
	if (child == 0) //child
	{
		child_process_single(cmd, data);
	}
	else if (child > 0) //parent
	{
		if (!wait_function(child, 0, data))
			return (0);
	}
	else if (child < 0)
		return (0); //error
	return (1);
}

/*fork a child need to execute builtin inside*/
int	exec_in_child_multi(t_scmd *cmd, t_data *data, int i)//need to call builtins here
{
	pid_t	child;

	child = fork();
	if (child == 0) //child
	{
		child_process_multi(cmd, data);
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
	if (!is_builtin(cmd))
	{
		if (!execve_param(data))
			return (0); //set errno and return FAILURE
	}
	ret = exec_in_child_multi(cmd, data, i);//executer return 0 for error and errno will be set and close
	if (!is_builtin(cmd))
		free_execve_param(data);
	parent_close(fd, i, data->n_pipes);
	return (ret);// success
}

/*builtin->save and reset std_fd, execve->create and free param*/
int	executer_single(t_scmd *cmd, t_data *data)
{
	int	saved_out;
	int saved_in;
	int	ret;

	if (is_builtin(cmd))
	{
		if (!save_std_fd(&saved_in, &saved_out))
			return (0); //error in dup
		ret = execute_builtin(cmd, data);
		if(!reset_std_fd(saved_in, saved_out))
			return (0); //error in dup2
	}
	else
	{
		if(!execve_param())
			return(0);
		ret = exec_in_child_single(cmd, data);
		free_execve_param(data);
	}
	return (ret);
}

/*if n_pipes present call multi command, otherwise single*/
int executer(t_scmd *cmd, t_data *data)
{
	int		i;
	t_scmd	*ptr;

	data->cmd_path = 0;
	data->envp_ar = 0;
	data->cmd_args = 0;
	if (data->n_pipes)
	{
		i = 0;
		ptr = cmd;
		while (ptr)
		{
			if (!executer_multi(cmd, data, i))
				return (0);
			ptr = ptr->next_cmd;
			i++;
		}
	}
	else
	{
		if (!executer_single(cmd, data));
			return (0);
	}
	return (1);
}
