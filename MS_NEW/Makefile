# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 22:05:24 by dantonik          #+#    #+#              #
#    Updated: 2022/10/25 00:57:52 by dantonik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

AUTHORS = dantonik, cboubour
DATE = $$(date +%Y/%m/%d)

CC = cc
FLAGS = -Wall -Wextra -Werror
HEADERS = -I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBFT = ./lib/libft
OBJDIR = obj
LIBSDIR	= lib
DLDIR = DL
LIBA = ./lib/libft/libft.a
SRC = main.c \
	lexer/lexer.c \
	lexer/handle_string.c \
	linked_list/linked_list.c

VPATH = src

RED			=	\033[0;31m
LBLUE		=	\033[1;34m
LCYAN		=	\033[1;36m
PURPLE		=	\033[0;35m
YELLOW		=	\e[38;5;226m
OK_COLOR	=	\033[0;32m
NO_COLOR	=	\033[m

# READLINE	=	-I~/.brew/opt/readline/include
# LIBRARY		=	-L$$HOME/.brew/opt/readline/lib -lreadline
# INCREADH 	=	-I /Users/$(USER)/.brew/opt/readline/include
# INCREADL 	=	-lreadline -L /Users/$(USER)/.brew/opt/readline/lib
INCLUDES = -I$(DLDIR)/readline_out/include -Ilibft -Iincludes
LDFLAGS = -L$(DLDIR)/readline_out/lib -lreadline

OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all: $(NAME)

# $(OBJDIR)/%.o: %.c | $(OBJDIR)
# 	@$(CC) $(INCREADH) -c $^ -o $@
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@$(CC) $(INCLUDES) -c $^ -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p obj/lexer
	@mkdir -p obj/env
	@mkdir -p obj/builtins
	@mkdir -p obj/linked_list

# $(NAME): $(OBJ) $(LIBFT) inc/minishell.h
# 	gcc $(FLAGS) $(OBJ) $(LIBFT) $(READLINE) $(INCREADL) $(LIBRARY) -o $(NAME)
$(NAME): $(DLDIR) $(OBJS) $(LIBFT) inc/minishell.h inc/structs.h | $(LIBA)
	@gcc $(FLAGS) $(OBJS) $(LIBA) $(INCLUDES) $(LDFLAGS) -o $(NAME)
	@printf "$(YELLOW)\n\t      -> Building $(NAME) ...$(RESET)\n"

$(LIBA):
	@make -C ./lib/libft/
	@make clean -C ./lib/libft/

$(DLDIR):
	@printf "$(YELLOW)\n\t      -> Downloading readline ...$(RESET)\n"
	@mkdir -p $(DLDIR)
	@curl -s https://ftp.gnu.org/gnu/readline/readline-8.1.2.tar.gz --output $(DLDIR)/readline-8.1.2.tar.gz > /dev/null
	@tar xfz $(DLDIR)/readline-8.1.2.tar.gz -C $(DLDIR)
	@printf "$(YELLOW)\n\t      -> Building readline ...$(RESET)\n"
	@cd $(DLDIR)/readline-8.1.2; ./configure --prefix=$(PWD)/$(DLDIR)/readline_out > /dev/null; cd ../../;
	@cd $(DLDIR)/readline-8.1.2; make -s > /dev/null 2> /dev/null; make -s install > /dev/null 2> /dev/null;

debug:
	$(MAKE) CFLAGS='-g -fsanitize=address,undefined' re

clean c:
	@if [ -d "obj" ]; then \
		rm -rf $(OBJDIR); \
		printf "%-53b%b" "$(PURPLE)obj folder deleted:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"; \
	fi
	@make clean -C ./lib/libft/
	@printf "%-53b%b" "$(LBLUE)libft clean:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"
	@printf "\n"

fclean f: clean
	@make fclean -C ./lib/libft/
	@if [ -f "minishell" ]; then \
		rm -rf $(NAME); \
		printf "%-53b%b" "$(PURPLE)minishell executable deleted :" "$(OK_COLOR)[✓]$(NO_COLOR)\n"; \
	fi
	@if [ -d "DL" ]; then \
		rm -rf $(DLDIR); \
		printf "%-53b%b" "$(PURPLE)Downloads deleted :" "$(OK_COLOR)[✓]$(NO_COLOR)\n"; \
	fi
	@printf "%-53b%b" "$(LCYAN)libft fclean:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"
	@printf "\n"


re r: fclean all

.PHONY:
	clean fclean re c f r all