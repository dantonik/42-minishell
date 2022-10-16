# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/04 00:19:43 by cboubour          #+#    #+#              #
#    Updated: 2022/07/04 00:19:43 by cboubour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
NAME = pipex
LIBFT = libft/libft.a
SRC = pipex.c utils.c

OBJ = 	$(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	gcc -c $^ -o $@

$(NAME): $(OBJ) $(LIBFT) pipex.h
	gcc $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:
	make clean
	rm -f $(NAME)

re: fclean all

.PHONY:
	clean fclean re
