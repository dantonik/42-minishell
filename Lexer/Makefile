NAME = a.out
SRCS = src/lexer.c src/main.c src/token.c src/io.c
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra
FLAGS = -g -lm -ldl -fPIC -rdynamic

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c inc/minishell.h
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(NAME)
	rm -rf src/*.o
