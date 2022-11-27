/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 11:08:46 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/27 10:39:18 by lisa          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

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
int	prompt_call(t_data *data)
{
	char	*input;
	t_scmd	*cmd;

	cmd = NULL;
	while (1)
	{
		input = get_rl();
		//printf("input = \"%s\"\n", input); //to show what we got from input
		if (!lexer(input, data))
			return (0); //stop and return
		// /expander(data);
		//cmd = parser(data);
		//if (!cmd)
		// 	return (0);
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
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}
