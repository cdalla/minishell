#ifndef MINISHELL_H
# define MINISHELL_H

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/wait.h>
#include "./libft/libft.h"

enum	token_type
{
	WORD = 1,
	PIPE = 2,	// |
	READ = 3,	//redirection input <
	WRITE = 4,	//redirection output >
	APPEND = 5,	//redirection out append >>
	HEREDOC = 6,	//heredoc <<
};

enum	cmd_type
{
	SIMPLE_CMD = 1,	//head of a single command
	ARGUMENT = 2,
};

enum	var_type
{
	SHELL = 1,
	ENV = 2,
};

typedef struct s_file
{
	char 			*filename;
	enum token_type type;
	struct s_file 	*next;
}				t_file;

typedef struct s_scmd
{
	enum cmd_type	type;
	char			*value;
	struct s_scmd	*next_cmd;
	struct s_scmd	*cmd_name;
	struct s_scmd	*next_arg;
	t_file			*file;
}				t_scmd;

typedef struct s_envp
{
    char			*env;
    char			*value;
	char			*input;
	enum var_type	type;
    struct s_envp	*next;
    struct s_envp	*prev;
    struct s_envp	*last_node;
}   t_envp;

typedef struct s_token
{
    char		    	*word;
    enum token_type 	type;
    struct s_token  	*next;
}               t_token;

typedef struct s_data
{
    t_envp          *envp;
    t_token         *token;
	char			*cmd_path;
	char			**envp_ar;
	char			**cmd_args;
	int            	n_pipes;
	int				to_write;
	int				to_read;
	int				to_close;
	int				exit_code;
}   t_data;

//LEXER
int		prompt_call(t_data *data);
int		add_env(t_envp **envp, char *args, enum var_type type);
void	print_env_var(t_envp *envp);
int		lexer (char	*input, t_data *data);
int		is_space(int c);
int		type_recogn(char *word);
int		is_redirection(char *c);
char	*get_rl(void);
void 	quote_check(int *quote, int *dquote, int c);
int		check_shell_var(t_data	*data);
int		check_var_syntax(char *str);
t_envp	*var_exist(t_envp *envp, char *name);
int		update_var_value(t_envp *envp, t_envp *var, char *value, int type);
int		add_var(t_data *data, char *str, enum var_type type);
char 	*get_env_value(char *name, t_data *data);
int		quote_removal(t_token *token);

//STRUCT TOKEN
int 	add_token(t_token **token, char *word, int type);
void	free_tokens(t_data *data);
void    print_tokens(t_token *token);

t_scmd	*new_scmd(enum cmd_type type);
int		add_scmd_arg(t_scmd *cmd, t_scmd *arg);
int		set_scmd_value(t_scmd *cmd, char *value);
void 	print_scmd(t_scmd *cmd);//to remo
void 	print_multi_cmd(t_scmd *cmd_line, int n_pipes);//to remo
int		add_file(t_scmd *cmd, enum token_type type, char *value);
void 	free_cmd(t_scmd *cmd);

//PARSER
t_scmd 	*parser(t_data *data);
int		parse_loop(t_scmd *cmd, t_token **token, int line);
int		parse_single_token(t_token *ptr, t_scmd *cmd);
int		parse_red(t_token *ptr, t_scmd *cmd);
int		count_pipes(t_token *token);

//EXECUTER
char 	**split_paths(t_data *data);
char	*join_cmd_name(char *cmd_name, char **paths);
char 	*check_path_cmd(char *cmd_name, t_data *data);
char 	**ls_toarr_args(t_scmd *list, char *cmd_name);
char 	**cpy_list_args(t_scmd *list, int size, char *cmd_name);
char 	**ls_toarr_env(t_envp *list);
char 	**cpy_list_env(t_envp *list, int size);
int		is_builtin(t_scmd *cmd);
int		execute_builtin(t_scmd *cmd, t_data *data);
int		set_red(t_file *file, t_data *data);

int	remove_envp(t_envp **envp, t_envp *to_rem);
int	print_err_msg(int exit_code, char *str);




#endif