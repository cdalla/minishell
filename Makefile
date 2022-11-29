NAME := minishell

CC := gcc

CFLAGS := -g -Wall -Werror -Wextra -fsanitize=address

HEADER := src/minishell.h

LIBFT := src/libft/libft.a

LIBREADLINE =  -L /Users/$(USER)/.brew/opt/readline/lib/ 

OBJ :=	obj/lexer/lexer_utils.o\
		obj/lexer/lexer.o\
		obj/lexer/read_line.o\
		obj/parser/parser.o\
		obj/parser/parser_utils.o\
		obj/structures/s_envp.o\
		obj/structures/s_exit_code.o\
		obj/structures/s_redirection.o\
		obj/structures/s_scmd.o\
		obj/structures/s_token.o\
		obj/structures/free_scmd.o\
		obj/executer/executer.o\
		obj/executer/cmd_path.o\
		obj/executer/list_to_array.o\
		obj/main.o\


SRC :=	src/lexer/lexer_utils.c\
		src/lexer/lexer.c\
		src/lexer/read_line.c\
		src/parser/parser.c\
		src/parser/parser_utils.c\
		src/structures/s_envp.c\
		src/structures/s_exit_code.c\
		src/structures/s_redirection.c\
		src/structures/s_scmd.c\
		src/structures/s_token.c\
		src/structures/free_scmd.c\
		src/executer/executer.c\
		src/executer/cmd_path.c\
		src/executer/list_to_array.c\
		src/main.c\


all: $(NAME)
	
$(NAME): $(LIBFT) $(OBJ) 
	@$(CC) $(CFLAGS) $(LIBREADLINE) -o $@ $^  -lreadline 

obj/%.o: src/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $< -I /Users/$(USER)/.brew/opt/readline/include/

$(LIBFT):
	make -C ./src/libft

clean:
	rm -f $(OBJ)
	make clean -C ./src/libft/
	rmdir obj/lexer obj/parser obj/structures obj/executer obj

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

.PHONY: all, clean, fclean, re
