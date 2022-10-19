FLAGS = -Wall -Wextra -Werror
NAME = minishell
LIBFT = libft/libft.a
READLINE = -I~/.brew/opt/readline/include
LIBRARY = -L$$HOME/.brew/opt/readline/lib -lreadline
SRC = main.c linked_list.c lexer.c

OBJ = 	$(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	gcc -c $^ -o $@

$(NAME): $(OBJ) $(LIBFT) minishell.h
	gcc $(FLAGS) $(OBJ) $(LIBFT) $(READLINE) $(LIBRARY) -o $(NAME)

clean c:
	rm -f $(OBJ)

fclean f:
	make clean
	rm -f $(NAME)

re r: fclean all

.PHONY:
	clean fclean re c f r