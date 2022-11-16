#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "./libft/libft.h"

enum	token_type
{
	WORD = 1,
	PIPE = 2,	// ||
	REDI = 3,	//redirection input <
	REDO = 4,	//redirection output >
	REDOA = 5,	//redirection out append >>
	HERED = 6,	//heredoc <<
};

enum	cmd_type
{
	SIMPLE_CMD = 1,	//head of a single command
	ARGUMENT = 2,
};

enum	red_type
{
	APPEND = 1,
	WRITE = 2,
	HERED = 3,
	READ = 4,
};

typedef struct s_infile
{
	char			*filename;
	enum red_type	type;
	struct s_infile *next;
};

typedef struct s_outfile
{
	char 			*filename;
	enum red_type 	type;
	strcut s_oufile *next;
};

typedef struct s_scmd
{
	enum cmd_type	type;
	char			*value;
	struct s_scmd	*cmd_name;
	struct s_scmd	*next_arg;
	struct s_scmd	*prev_arg;
	struct s_infile	*infile;
	struct s_outfile *outfile;
}				t_scmd;

typedef struct s_envp
{
    char *env;
    char *value;
    struct s_envp *next;
    struct s_envp *prev;
    struct s_envp *last_node;
}   t_envp;

typedef struct s_token
{
    char		    	*word;
    enum token_type 	type;
    struct s_token  	*next;
}               t_token;

typedef struct s_exit_code
{
    int                 exit_code;
    char                *exited_cmd;
    struct s_exit_code  *next;
    struct s_exit_code  *prev;
}   t_exit_code;

typedef struct s_data
{
    t_exit_code     *exit_code;
    t_envp          *envp;
    t_token         *token;
    bool            pipe_flag;
}   t_data;

int unset(t_envp **envp, char *var);

//LEXER
int		prompt_call(t_data *data);
char	*get_rl(void);
int		lexer (char	*input, t_data *data);

//STRUCT 
int 	add_token(t_token **token, char *word, int type);
void	free_tokens(t_data *data);
void    print_tokens(t_token *token);
#endif