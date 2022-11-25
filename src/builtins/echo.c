#include "./../minishell.h"
//no trimming for spaces as no handling for 
int    echo(char *options, char *str)
{
    int status;

    if(!str)
        return(-1);
    status = printf(str);
    if(status != -1 && ft_strcmp(options, "-n") != 0) //no write error and no flag
        status = printf("\n"); //print \n
    if(status == -1)
        return (-1);
    return (0); 
}
//do echo edge cases 
//	spaces trimming ect.. run tests