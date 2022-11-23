#include <stdio.h>
#include "../src/minishell.h"

typedef struct s_lst
{
	void *next;
	char *value;
}			t_lst;

int	list_size(t_lst *list)
{
	t_lst 	*ptr;
	int		size = 0;


	ptr = list;
		
	while(ptr)
	{	
		size++;
		printf("%s\n", ptr->value);
		ptr = ptr->next;
	}
	return (size);
}

int	add_env(t_envp **envp, char *args);
void    print_env_var(t_envp *envp);

int	env_save(t_envp **s_envp, char **envp)
{
	int	i;

	i = 0;
	while(envp[i])
	{
		if (!add_env(s_envp, envp[i]))
			return (0); //failure and free all the malloced mem
		i++;
	}
	return (1); //success
}

int main(int argc, char **argv, char **envp)
{
	int i = 0; 
	// int size = 1;
	// while (i++ < 10 && size)
	// 	printf("%d\n", size);
	// printf("%d\n", i);
	t_envp *envp_s = 0;

	env_save(&envp_s, envp);
	//print_env_var(envp_s);
	printf("ok\n");
	printf("%d\n",list_size((t_lst *)envp));
	return (0);
}