int look_for_path(char **cd_paths, char *dir)
{
    int     error;
    char    *path;

    if(!cd_paths)
        error = chdir(dir);
    while (cd_paths)
    {
        path = ft_strjoin(cd_paths, dir);
        if (!path)
            return (NULL);
        if((error = chdir(path)) == 0)
            break;
        cdpath++;
    }
    if (error == -1)
        return(errno);
    else if(error == 0 || *dir == '-')
        pwd(path);
    return(1);
}

int success_config(char *new_dir, char *prev_dir, t_envp *envp)
{
    int flag;

    flag = 0;
    while(envp)
    {
        if(ft_strcmp(envp->env, "PWD"))
        {
            envp->value = new_dir;
            flag++;
        }
        if(ft_strcmp(envp->env, "OLDPWD"))
        {
            envp->value = old_dir;
            flag++;
        }
        if (flag == 2)
            break;
        envp = envp->next;
    }
    return (0);
}

char *get_env_var(t_envp *envp, char *env)
{
    while(envp)
    {
        if(ft_strcmp(envp->env, env) == 0)
            return(envp->val);
        envp = envp->next;
    }
    return (NULL);
}

int configure_options(char  *dir, char **cdpath_split, t_envp *envp)
{
    if (!*directory)
        directory = get_env_var(envp, "HOME");
    if (!directory)
        return(0);
    if (directory == '-')
    {
        directory = get_env_var(envp, "OLDPWD");
        if (!directory)
            return (0);
    }
    if(*directory != '/')
    {
        cdpath = get_env_var(envp, "CDPATH");
        if(!cdpath)
            return(0);
        cdpath_split = ft_split(cdpath), ':';
        if(!cdpath_split)
            return(NULL);
    }
    return(1);
}

int cd(char *old_dir, t_envp *envp)
{
    char    *cdpath;
    char    **cdpath_split;
    char    *new_dir;
    cdpath_splitted = NULL;

    if(configure_options(old_dir, cdpath_split, envp)
    {
        if (look_for_path(cdpath_split, directory))
        {
            success_config(new_dir, old_dir, envp);
            return (0);
        }
    }
    return (-1);
}

/*
change current working directory to directory -- chdir
If directory is not supplied, the value of the HOME shell variable is used. --getenv("HOME")
If the shell variable CDPATH exists, it is used as a search path: each directory name in CDPATH is searched for directory, --look_for_path
with alternative directory names in CDPATH separated by a colon (‘:’). If directory begins with a slash, CDPATH is not used. -- ft_split(cdpath, ':')
If directory is ‘-’, it is converted to $OLDPWD before the directory change is attempted. // l32

If ‘..’ appears in directory, it is processed by removing the immediately preceding pathname component, back to a slash or the beginning of directory. --> autoamtic handling

If a non-empty directory name from CDPATH is used, or if ‘-’ is the first argument, and the directory change is successful, the absolute pathname of the new working directory is written to the standard output.

If the directory change is successful, 
cd sets the value of the PWD environment variable to the new directory name,
and sets the OLDPWD environment variable to the value of the current working directory before the change. -->configure_success
The return status is zero if the directory is successfully changed, non-zero otherwise.

*/