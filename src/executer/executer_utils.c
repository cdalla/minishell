#include "../minishell.h"

void	set_fd(t_data *data, int fd[2][2], int i)
{
	data->to_close = -1;
	data->to_read = 0;
	data->to_write = 1;
	if (i % 2)
	{
		if (i < data->n_pipes)
		{
			data->to_close = fd[1][0];
			data->to_write = fd[1][1];
		}
		data->to_read = fd[0][0];
	}
	else
	{
		if (i < data->n_pipes)
		{
			data->to_close = fd[0][0];
			data->to_write = fd[0][1];
		}
		if(i != 0)
			data->to_read = fd[1][0];
	}
}

void	parent_close(int fd[2][2], int i, int n_pipes)
{
	if (i % 2)
	{
		if (i < n_pipes)
			close(fd[1][1]);
		close(fd[0][0]);
	}
	else
	{
		if (i < n_pipes)	
			close(fd[0][1]);
		if (i != 0)
			close(fd[1][0]);
	}
}

void	print_dsarry(char **array)//just for testing purpose !!!REMOVE!!!
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}
