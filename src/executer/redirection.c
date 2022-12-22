/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/29 19:46:09 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/12/22 19:50:48 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

/*open the outfile*/
int	set_outfile(t_file *file, t_data *data)
{
	if (data->to_write != -1)
	{
		if (close(data->to_write) == -1)
			printf("close infile error\n");//close fd set previously
	}
	if (file->type == APPEND)
	{
		data->to_write = open(file->filename, O_WRONLY | O_APPEND | O_CREAT , 0777);
		if (data->to_write == -1)
			return (0); //error
	}
	else
	{
		data->to_write = open(file->filename, O_WRONLY | O_CREAT , 0777);
		if (data->to_write == -1)
			return (0); //error
	}
	return (1);
}

// int	write_in_file(int fd, char **del)
// {
// 	char	*str = NULL;
		
// 	while (1)
// 	{
// 		if (str) //if read_line is something
// 		{
// 			free(str);
// 			str = NULL;
// 		}
// 		str = readline(">");
// 		if (!ft_strncmp(*del, str, ft_strlen(*del) + 1))
// 			break ;
// 		if (write(fd, str, ft_strlen(str)) == -1)
// 			printf("write in heredoc %s\n", strerror(errno));
// 		write(fd, "\n", 1);
// 	}
// 	return (1);
// }

// /*open a temporary file, write with input save the file*/
// int	set_heredoc(char **del, t_data *data)
// {
// 	data->to_read = open("test_file" , O_WRONLY | O_APPEND |  O_CREAT , 0777);
// 	if (data->to_read == -1)
// 	{
// 		write(1, "not open in heredoc\n", 21);
// 		return (0);//file not opened
// 	}
// 	else
// 	{
// 		write_in_file(data->to_read, del);
// 		free(*del);
// 		*del = ft_strdup("test_file");//save the tmp char
// 		if(close(data->to_read) == -1)
// 			printf("error close in heredoc\n");
// 	}
// 	return (1); //success
// }

/*open infile or heredoc*/
int	set_infile(t_file *file, t_data *data)
{
	if (data->to_read != -1)
	{
		if (close(data->to_read) == -1)
			printf("close error infile\n");
	}
	// if (file->type == HEREDOC)//check if we need to manage heredoc if something fails before
	// {
	// 	if (access("test_file", F_OK) == 0)
	// 		unlink("test_file");
	// 	if (!set_heredoc(&file->filename, data))
	// 	{
	// 		printf("file not opened in heredoc\n");
	// 		return (0);
	// 	}
	// }
	printf("open file %s\n", file->filename);
	data->to_read = open(file->filename, O_RDONLY);
	if (data->to_read == -1)
	{
		printf("after open %s\n", strerror(errno));
		return (0); //error
	}
	return (1);
}

/*dup2 of correct fd and then close it*/
int	dup_close(t_data *data)
{
	if (data->to_read != -1)
	{
		dup2(data->to_read, STDIN_FILENO);
		close(data->to_read);
	}
	// if (access("test_file", F_OK) == 0)
	// 	unlink("test_file");
	if (data->to_write != -1)
	{
		dup2(data->to_write, STDOUT_FILENO);
		close(data->to_write);
	}
	return (1);
}

/*loop file list and call open file funct*/
int	set_red(t_file *file, t_data *data)
{
	while(file)
	{
		if (file->type == READ || file->type == HEREDOC)
		{
			if (!set_infile(file, data))
				return (0);
		}
		else
		{
			if (!set_outfile(file, data))
				return (0);
		}
		file = file->next;
	}
	dup_close(data);
	return(1);
}
