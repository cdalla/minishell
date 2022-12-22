/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 11:08:46 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/22 16:36:50 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

/*
	called by main
	prompt function call the prompt and pass the input 
	need to stop with exit_builtin
*/
int executer(t_scmd *cmd, t_data *data);
int	expander(t_data *data);

/*handle the signal*/
void	sigint_handler(int signum)
{
	//printf("\n");
	write(1, "\n",1);
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
	(void)signum;
}

/*catch the correct signal*/
void	signals(void)
{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
}

/*get input from f_readline, add it history*/
char	*get_rl(void)
{
	static char	*line_read;

	line_read = NULL;
	if (line_read) //if read_line is something
	{
		free(line_read);
		line_read = NULL;
	}
	line_read = readline("pizzamandolino>");
	if (!line_read || !ft_strncmp(line_read, "exit", 5))
	{
		ft_putendl_fd("exit", 1);
		return (0);
	}
	else if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

/*call different part of shell, return  exit_status*/
int	input_interpreter(char *input, t_data *data)
{
	t_scmd	*cmd;

	cmd = NULL;
	if (!lexer(input, data))
	{
		printf("lexer error\n");
		return (0); //return 0 only for malloc fail, also if quotes are still open
	}
	if (!expander(data))
	{
		printf("expander error\n");
		return(0); //malloc error
	}
	if (!quote_removal(data->token))
	{
		printf("quote removal error\n");
		return (0); //malloc fail
	}
	cmd = parser(data);
	//print_multi_cmd(cmd, data->n_pipes);
	if (data->token)
	{
		if (!cmd)
		{
			printf("parser error\n");
			return (0); //malloc fail
		}
		if (!executer(cmd, data))
		{
			printf("executer error\n");
			return(0);
		}
		free_cmd(cmd);
	}
	return (1);
}

/*loop get input from command line, call intepreter, print exit status*/
int	prompt_call(t_data *data)
{
	char	*input;
	while (1)
	{	
		//status = 0;
		data->to_close = -1;
		data->to_read = -1;
		data->to_write = -1;
		//signals();
		input = get_rl();
		if (!input)
			exit(0); // get exit or CTRL D by readline
		if (!input_interpreter(input, data))
		{
			if (errno)
				printf("errno %d = %s\n", errno, strerror(errno));
			// if (status && status != 256)
			// 	printf("status %d = %s\n", status, strerror(status));
		}
		free_tokens(data);
	}
}
