NAME := minishell

FLAGS = -Wall -Wextra -Werror

SRC = test.c linked_list.c

OBJS = $(SRC:.c=.o)

INCLUDES = -Llibft

all: $(NAME)

%.o: %.c
	@cc -c $^ -o $@

$(NAME): $(OBJS) minishell.h
	@cc $(FLAGS) $(OBJS) libft/libft.a -o $(NAME)

LSANLIB = LeakSanitizer/liblsan.a
lsan: FLAGS += -ILeakSanitizer -Wno-gnu-include-next -LLeakSanitizer -llsan -lc++
lsan: fclean $(LSANLIB)
lsan: all

$(LSANLIB): 
	@if [ ! -d "LeakSanitizer" ]; then git clone --recursive git@github.com:mhahnFr/LeakSanitizer.git; fi
	@make -C LeakSanitizer

run: all
	@./$(NAME)

test : $(TOBJS) $(OBJS)
	@$(CC) $(TOBJS) $(OBJS) -o $(TEST)
	@./$(TEST)

clean c:
	@rm -rf *.o

fclean f: clean
	@rm -f $(NAME)

re r: fclean all

.PHONY:
	clean fclean re c f r all