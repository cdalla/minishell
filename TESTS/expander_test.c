#include <stdio.h>
#include "../minishell.h"

int	env_save(t_envp **s_envp, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!add_env(s_envp, envp[i], 2))
			return (0); //failure and free all the malloced mem
		i++;
	}
	return (1); //success
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc > 2 || !argv)
		return (0);
	(void)argc;
	(void)argv;
	data.envp = NULL;
	data.token = NULL;
	data.exit_code = NULL;
	env_save(&data.envp, envp);
	exit(0);
	return (0);

	
}