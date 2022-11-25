#include "./../minishell.h"

// int is_str_valid(char *str)
// {
// 	if (*str && (*str == '_' || ft_isalpha(*str)))
// 	{
// 		str++;
// 		while (*str && (ft_isalnum(*str) || *str == '_'))
// 			str++;
// 		if (!*str)
// 			return (1);
// 	}
// 	printf("bash: export: %s is not a valid identifier\n", str);
// 	return(0);
// }
    
char **ft_cut_string(char *str, bool *standalone)
{
    char *temp;
    char **splitted;

    temp = ft_strchr(str, '=');
    if(temp)
    {
		*standalone = false;
        *temp = '\0';
        temp++;
    }
	else
		*standalone = true;
    splitted = malloc(sizeof(char *) * 2);
    if(!splitted)
        return(NULL);
    splitted[0] = str;
    splitted[1] = temp;
    return(splitted);
}

int	format_and_add(t_envp **envp, char *arg)
{
	char 	**args;
	int		error;
	bool	standalone;

	args = ft_cut_string(arg, &standalone);
	if(!args)
		return(0);
	error = update_envp(*envp, args, standalone);
	if(error != 0)
		return (error);
	error = create_envp(args, envp, standalone);
	if (error <= 0)
		return (error); //failure
	return (error); //success
}
