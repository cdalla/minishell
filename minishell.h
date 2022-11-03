#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct s_envp
{
    char *env;
    char *value;
    t_envp *next;
    t_envp *prev;
    t_envp *last_node;
}   t_envp;

typedef struct s_token
{
    char		*word;
    int 		type;
    t_token		*next;
}               t_token;

typedef struct s_exit_code
{
    int         exit_code;
    char        *exited_cmd;
    t_exit_code *next;
    t_exit_code *prev;
}   t_exit_code;

typedef struct s_data
{
    t_exit_code     *exit_code;
    t_envp          *envp;
    t_token         *token;
    bool            pipe_flag;
}   t_data;

int unset(t_envp **envp, char *var);

#endif