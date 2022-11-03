GCC = gcc

CFLAGS = -Wall -Wextra -Werror

HEADER = ./minishell.h

NAME = minishell.a

OBJECTS =   ./builtins/unset.o \
			./TESTS/builtins_test.o 

#./builtins/cd.o \
			./builtins/echo.o \
			./builtins/env.o \
			./builtins/exit.o \
			./builtins/export.o \
			./builtins/pwd.o 

.PHONY: all fclean clean re

all: $(NAME)

$(NAME): $(OBJECTS)
	make -C ./libft
	cp ./libft/libft.a ./minishell.a
	ar rc $@ $^
	$(CC) $(CFLAGS) -o $@ ./minishell.a

$(OBJECTS): $(HEADER)

clean:
	rm -f $(OBJECTS) && make clean -C ./libft/

fclean: clean
	rm -f $(NAME) && make fclean -C ./libft/

re:	fclean all
