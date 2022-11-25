#include "./../minishell.h"

int check_and_format_arguments(char **str)
{
    char *new_str;

    if(**str)
    {
        new_str = ft_strtrim(*str, " ");
            //free(new_str);
        if (ft_strchr(new_str, ' '))
            return(0);
        *str = new_str; 
    }
    return(1);
}

int change_directory(char **lst_cdpaths, char **dir, char *tmp_dir, t_envp *envp) //If the shell variable CDPATH exists, it is used as a search path: each directory name in CDPATH is searched for directory
{
    int     error;
    int     paths_usage;
    char    *path;

    paths_usage = 0; 
    while (lst_cdpaths && *lst_cdpaths)
    {

        *lst_cdpaths = ft_strjoin(*lst_cdpaths, "/");
        path = ft_strjoin(*lst_cdpaths, *dir);
        if (!path)
            return (NULL);
        if((error = chdir(path)) == 0) //success on 0
        {
            paths_usage = 1;
            break;
        }
        lst_cdpaths++;
    }
    error = chdir(*dir);
    if (error == -1)
        return(ERRARG_CD); //forgot **dir
    else if(error == 0 && paths_usage || *tmp_dir == '-') //‘-’ first argument, directory change successful,  absolute path new working directory written to the standard output.
            pwd(envp);                //If a non-empty directory name from CDPATH is used -- -- -- -- -- (read above)
    return(SUCCESS);
}


int configure_options(char  **dir, char ***lst_cdpath, t_envp *envp)
{
    char *cd_paths;

    if (!*dir || !**dir)
        *dir = get_envp(envp, "HOME"); //directory is not supplied, the value of the HOME shell variable is used.
    else if (**dir == '~')
    {   
        (*dir)++;
        *dir = ft_strjoin(get_envp(envp, "HOME"), *dir); //directory is not supplied, the value of the HOME shell variable is used.
    }
    else if (**dir == '-') //If directory is ‘-’, it is converted to $OLDPWD before the directory change is attempted.
        *dir = get_envp(envp, "OLD_PWD");
    else if(**dir != '/' && **dir != '.') //If directory begins with a slash, CDPATH is not used.
    {
        cd_paths = get_envp(envp, "PATH");
        if(cd_paths)
        {
            *lst_cdpath = ft_split(cd_paths, ':'); //alternative directory names in CDPATH separated by a colon (‘:’).
            if(!*lst_cdpath)
                return(ERRMALLOC);
        }
    }
    if(!*dir)
        return (-1);
    return (SUCCESS);
}

int cd(char *dir, t_envp *envp)
{
    char    *cdpath;
    char    **lst_cdpath;
    char    *tmp_dir;
    int     errno;
    char    s[100];

    lst_cdpath = NULL;
    cdpath = NULL;
    tmp_dir = dir;
    if(!check_and_format_arguments(&dir))
    {
        printf("bash: cd: too many arguments");
        return(WRGNUMARGS);
    }
    errno = configure_options(&dir, &lst_cdpath, envp);
    if (errno == SUCCESS)
    {
        if (change_directory(lst_cdpath, &dir, tmp_dir, envp) == SUCCESS)
        {
            export(&envp, ft_strjoin("OLD_PWD=", get_envp(envp, "PWD")));
            export(&envp, ft_strjoin("PWD=", getcwd(s, 100)));
        }
    }
    if(errno == ERRARG_CD)
        printf("bash: cd: %s", dir);
    return (errno); //dir not changed non-zero .
}
