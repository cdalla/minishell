/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 11:08:46 by cdalla-s      #+#    #+#                 */
/*   Updated: 2023/01/08 16:16:55 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

int		executer(t_scmd *cmd, t_data *data);
int		expander(t_data *data);
void	print_error(int err_num);
void	signals_parent(void);

/*get input from f_readline, add it history*/
char	*get_rl(void)
{
	static char	*line_read;

	line_read = NULL;
	if (line_read)
	{
		free(line_read);
		line_read = NULL;
	}
	rl_outstream = stderr;
	line_read = readline("pizzamandolino> ");
	if (!line_read)
	{
		ft_putendl_fd("exit", 2);
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
		return (print_err_msg(ret, "lexer"));
	ret = expander(data);
	if (ret)
		return (print_err_msg(ret, "expander"));
	ret = quote_removal(data->token);
	if (ret)
		return (print_err_msg(ret, "quote removal"));
	cmd = parser(data);
	if (data->token)
	{
		if (!cmd)
			return (print_err_msg(ret, "parser"));
		ret = executer(cmd, data);
		free_cmd(cmd);
		if (ret)
			return (ret);
	}
	return (print_err_msg(ret, ""));
}

/*loop get input from command line, call intepreter, print exit status*/
int	prompt_call(t_data *data)
{
	char	*input;

	while (1)
	{	
		data->to_close = -1;
		data->to_read = -1;
		data->to_write = -1;
		signals_parent();
		input = get_rl();
		if (!input)
			return(0);
		signal(SIGINT, SIG_IGN);
		data->exit_code = input_interpreter(input, data);
		//printf("exit code in promptcall = %d\n", data->exit_code);
		free(input);
		free_tokens(data);
	}
}
