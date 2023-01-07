NAME := minishell

CC := gcc

CFLAGS := -g -Wall -Werror -Wextra -fsanitize=address

HEADER := src/minishell.h

LIBFT := src/libft/libft.a

LIBREADLINE =  -L /Users/$(USER)/.brew/opt/readline/lib/ 

OBJ :=	obj/lexer/lexer_utils.o\
		obj/lexer/lexer.o\
		obj/lexer/read_line.o\
		obj/lexer/shell_var.o\
		obj/lexer/quote_remove.o\
		obj/expander/expander.o\
		obj/expander/expander_utils.o\
		obj/parser/parser.o\
		obj/parser/parser_utils.o\
		obj/structures/s_envp.o\
		obj/structures/s_envp_utils.o\
		obj/structures/s_redirection.o\
		obj/structures/s_scmd.o\
		obj/structures/s_token.o\
		obj/structures/free_scmd.o\
		obj/structures/free_token.o\
		obj/executer/executer.o\
		obj/executer/execve_cmd_path.o\
		obj/executer/execve_array.o\
		obj/executer/execve_args.o\
		obj/executer/executer_single.o\
		obj/executer/executer_multi.o\
		obj/executer/redirection.o\
		obj/executer/fd.o\
		obj/executer/builtin_execute.o\
		obj/builtins/cd.o\
		obj/builtins/echo.o\
		obj/builtins/env.o\
		obj/builtins/export.o\
		obj/builtins/export_utils.o\
		obj/builtins/pwd.o\
		obj/builtins/unset.o\
		obj/builtins/exit.o\
		obj/error/error_print.o\
		obj/heredoc/heredoc.o\
		obj/heredoc/heredoc_utils.o\
		obj/signals/signals.o\
		obj/main.o\


SRC :=	src/lexer/lexer_utils.c\
		src/lexer/lexer.c\
		src/lexer/read_line.c\
		src/lexer/shell_var.c\
		src/lexer/quote_remove.c\
		src/expander/expander.c\
		src/expander/expander_utils.c\
		src/parser/parser.c\
		src/parser/parser_utils.c\
		src/structures/s_envp.c\
		src/structures/s_envp_utils.c\
		src/structures/s_redirection.c\
		src/structures/s_scmd.c\
		src/structures/s_token.c\
		src/structures/free_scmd.c\
		src/structures/free_token.c\
		src/executer/executer.c\
		src/executer/execve_cmd_path.c\
		src/executer/execve_array.c\
		src/executer/execve_args.c\
		src/executer/executer_single.c\
		src/executer/executer_multi.c\
		src/executer/redirection.c\
		src/executer/fd.c\
		src/executer/builtin_execute.c\
		src/builtins/cd.c\
		src/builtins/echo.c\
		src/builtins/env.c\
		src/builtins/export.c\
		src/builtins/export_utils.c\
		src/builtins/pwd.c\
		src/builtins/unset.c\
		src/builtins/exit.c\
		src/error/error_print.c\
		src/heredoc/heredoc.c\
		src/heredoc/heredoc_utils.c\
		src/signals/signals.c\
		src/main.c\


all: $(NAME)
	
$(NAME): $(LIBFT) $(OBJ) 
	@$(CC) $(CFLAGS) $(LIBREADLINE) -o $@ $^  -lreadline 

obj/%.o: src/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $< -I /Users/$(USER)/.brew/opt/readline/include/ -I $(LIBFT)

$(LIBFT):
	make -C ./src/libft

clean:
	rm -f $(OBJ)
	make clean -C ./src/libft/
	rmdir obj/lexer obj/parser obj/structures obj/executer obj/expander obj/builtins obj/error obj/heredoc obj/signals obj

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

.PHONY: all, clean, fclean, re
