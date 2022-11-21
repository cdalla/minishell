/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 11:02:58 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/11/13 17:00:42 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
HEREDOC IMPLEMENTATION !!! GARBAGE DONT LOOK THIS FILE !!!!

	if we recognize an heredoc we open a multiline input until DELIMITER is passed as input

	No parameter and variable expansion, command substitution, arithmetic expansion,
	or filename expansion is performed on word. 
	
	If any part of word is quoted, the delimiter is the result of quote removal on delimiter word, 
	and the lines in the here-document are not expanded. 
	
	If word is unquoted, all lines of the here-document are subjected to parameter expansion, 
	command substitution, and arithmetic expansion, the character sequence \newline is ignored, 
	and ‘\’ must be used to quote the characters ‘\’, ‘$’, and ‘`’.


	heredoc has to:

	save the every line as a new input (seems bash does not save that in the history?)
	tokenize again the input
		if delimiter is quoted all the input are simple words
		if delimiter is NOT quoted type recognition is needed

	
	recognize the DELIMITER
	get the input from read_line while != DELIMITER
	save it in a new token
	type yes or not

*/

#include "../minishell.h"

int	heredoc(char **str, int	*w_len, t_data *data)
{
	char	*del;
	char	*input;
	int		del_len;

	
	*w_len = 0;
	input = NULL;
	del = trim_word(str, w_len);
	del_len = *w_len;
	//check if there are quotes or not in del
	input = readline(">");
	while (ft_strncmp(del, input, del_len))
	{		
		if (input && *input)
			tokenize(input, data, 1); //i need to change str pointer to be able to modofy it
		if (input)
		{
			free(input);
			input = NULL;
		}
		input = readline(">");
	}
}