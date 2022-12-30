/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 11:08:46 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/30 12:01:59 by cdalla-s      ########   odam.nl         */
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
int 	executer(t_scmd *cmd, t_data *data);
int		expander(t_data *data);
void	print_error(int err_num);

/*handle the signal*/
void	sigint_handler(int signum)
{
	write(1, "\n", 1);
	rl_on_new_line();
	// rl_replace_line("", 0);
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
	int		ret;

	cmd = NULL;
	ret = lexer(input, data);
	if (ret)
	{
		//printf("lexer error\n");
		return (ret); //return 0 only for malloc fail, also if quotes are still open
	}
	ret = expander(data);
	if (ret)
	{
		//printf("expander error\n");
		return(ret); //malloc error
	}
	ret = quote_removal(data->token);
	if (ret)
	{
		//printf("quote removal error\n");
		return (ret); //malloc fail
	}
	cmd = parser(data);
	//print_multi_cmd(cmd, data->n_pipes);
	if (data->token)
	{
		if (!cmd)
		{
			//printf("parser error\n");
			return (107); //malloc fail
		}
		ret = executer(cmd, data);
		if (ret)
		{
			printf("executer error\n");
			return(ret);
		}
		free_cmd(cmd);
	}
	return (ret);
}

/*loop get input from command line, call intepreter, print exit status*/
/*err_num become part of struct and be printed with $?*/
int	prompt_call(t_data *data)
{
	char	*input;
	int		err_num;
	
	while (1)
	{	
		data->to_close = -1;
		data->to_read = -1;
		data->to_write = -1;
		signals();
		input = get_rl();
		if (!input)
			exit(0); // get exit or CTRL D by readline
		err_num = input_interpreter(input, data);
		if (err_num)
			print_error(err_num);
		free_tokens(data);
	}
}
