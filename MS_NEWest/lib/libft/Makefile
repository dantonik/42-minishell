# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/19 15:19:27 by dantonik          #+#    #+#              #
#    Updated: 2022/10/25 00:28:07 by dantonik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

LIBDIR = ../libs/

LCYAN		= \033[1;36m
COM_COLOR	= \033[0;34m
OBJ_COLOR	= \033[0;36m
OK_COLOR	= \033[0;32m
ERROR_COLOR	= \033[0;31m
WARN_COLOR	= \033[0;33m
NO_COLOR	= \033[m
COM_STRING	= "compiling"

GREEN		=	\e[38;5;118m
YELLOW		=	\e[38;5;226m
BRed		=	\033[1;31m
RESET		=	\e[0m
_TEST		=	[$(BRed)TEST$(RESET)]
_SUCCESS	=	[$(GREEN)SUCCESS$(RESET)]
_CLEAN		=	[$(YELLOW)CLEAN$(RESET)]
_FCLEAN		=	[$(YELLOW)FCLEAN$(RESET)]

FILES = ft_isalnum.c 		\
		ft_isalpha.c 		\
		ft_isascii.c 		\
		ft_isdigit.c 		\
		ft_isprint.c 		\
		ft_tolower.c 		\
		ft_toupper.c 		\
		ft_strchr.c	 		\
		ft_strrchr.c 		\
		ft_strlen.c  		\
		ft_strncmp.c 		\
		ft_memset.c  		\
		ft_memchr.c  		\
		ft_memcpy.c  		\
		ft_bzero.c   		\
		ft_memcmp.c  		\
		ft_memmove.c 		\
		ft_strnstr.c 		\
		ft_strlcpy.c 		\
		ft_strlcat.c 		\
		ft_atoi.c	 		\
		ft_calloc.c	 		\
		ft_strdup.c 		\
		ft_substr.c 		\
		ft_strjoin.c		\
		ft_strtrim.c 		\
		ft_split.c			\
		ft_itoa.c	 		\
		ft_strmapi.c 		\
		ft_striteri.c		\
		ft_putchar_fd.c		\
		ft_putstr_fd.c		\
		ft_putnbr_fd.c		\
		ft_putendl_fd.c

BONUS = ft_lstnew.c			\
		ft_lstadd_front.c	\
		ft_lstsize.c		\
		ft_lstlast.c		\
		ft_lstadd_back.c	\
		ft_lstdelone.c		\
		ft_lstclear.c		\
		ft_lstiter.c		\
		ft_lstmap.c

OBJS =	$(FILES:.c=.o)
BONUSOBJ = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $^
	@printf "$(YELLOW)\n\t      -> Building $(NAME) ...$(RESET)\n"

%.o : %.c
	@$(CC) -c $(CFLAGS) $< -o $@

bonus : $(BONUSOBJ) $(NAME)
	@$(AR) $(NAME) $^

clean:
	@$(RM) $(OBJS) $(BONUSOBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: bonus clean fclean re all