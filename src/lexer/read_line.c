/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 11:08:46 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/29 18:24:57 by cdalla-s      ########   odam.nl         */
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
	maybe we can return a value to main for err handling
		we should pass to this function the s_data
		then call from here lexer
	OR
		we can pass back the string from input
		in this case we can merge this with get_rl()
*/
void	sigint_handler(int signum)
{
	//printf("\n");
	write(1, "\n",1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)signum;
}

void	signals(void)
{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
}

int executer(t_scmd *cmd, t_data *data);
int	prompt_call(t_data *data)
{
	char	*input;
	t_scmd	*cmd;

	cmd = NULL;
	while (1)
	{	
		signals();
		input = get_rl();
		if (!input)
			exit(0); // return the correct msg
		//printf("input = \"%s\"\n", input); //to show what we got from input
		if (!lexer(input, data))
			return (0); //stop and return
		// /expander(data);
		cmd = parser(data);
		if (!cmd)
			return (0);
		executer(cmd, data);
		free_tokens(data);
		free_cmd(cmd);
	}
}

//get the line from prompt and return the string
//add error return
char	*get_rl(void)
{
	static char	*line_read;

	line_read = NULL;
	if (line_read) //if read_line is something
	{
		free(line_read);
		line_read = NULL;
	}
	line_read = readline("pouetpolpet>");
	if (!line_read)
	{
		ft_putendl_fd("exit",1);
		return (0);
	}
	else if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}
