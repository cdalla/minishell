/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 15:07:21 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/21 13:48:28 by cdalla-s      ########   odam.nl         */
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

/*fork a child process, call execution of single cmd*/
int	executer_single(t_scmd *cmd, t_data *data, int i, int multi)//need to call builtins here
{
	pid_t	child;
	//int		status;

	child = fork();
	if (child == 0)
	{
		if (multi)
		{
			if(is_builtin(cmd))
			{
				execute_builtin(cmd, data);
				exit(0);
			}
		}
		if (!cmd_start(cmd, data))
		{
			
			exit (0);
		}	
	}
	else if (child > 0)
	{
		if (i == data->n_pipes)
		{
			waitpid(child, &status, 0);
			//wait(NULL);
		}
		if (status != 0)
		{
			printf("execve error process i = %d\n", i);
			return (0);
		}
	}
	else if (child < 0)
	{
		printf("child error\n");
		return (0); //error
	}
	return (1);
}

/*set pipes, set fd, call execution of every command, close fd*/
int	executer_multi(t_scmd *cmd, t_data *data)
{
	t_scmd	*ptr;
	int		fd[2][2];
	int		i;

	i = 0;
	ptr = cmd;
	while(ptr)
	{
		//print_scmd(ptr);
		if (i < data->n_pipes)
		{
			if (pipe(fd[i % 2]) == -1)
			{
				printf("pipe error\n");
				return (0); //pipe error
			}
		}
		set_fd(data, fd, i);
		if (!executer_single(ptr, data, i, 1))
				return (0); //executer return 0 for error and errno will be set and close 
		parent_close(fd, i, data->n_pipes);
		ptr = ptr->next_cmd;
		i++;
	}
	return (1);// success
}

/*if n_pipes present call multi command, otherwise single*/
int executer(t_scmd *cmd, t_data *data)
{
	int	saved_out;
	int saved_in;

	if (data->n_pipes)
	{
		if (!executer_multi(cmd, data))
			return (0);
	}
	else
	{
		if (!save_std_fd(&saved_in, &saved_out))
			return (0); //error in dup
		if(!is_builtin(cmd)) //check better builtins return to catch error
		{
			if(!executer_single(cmd, data , 0, 0))
				return(0); //errno set by execve
		}
		else
		{	
			if (!execute_builtin(cmd, data))
			{
				printf("error execute builting in single\n");
			}
			if (!reset_std_fd(saved_in, saved_out))
				return (0); //error in dup2
		}
	}
	return (1);
}
