# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 22:55:36 by estruckm          #+#    #+#              #
#    Updated: 2023/04/10 17:11:22 by estruckm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRCS =	main.c \
		pipex_utils.c \
		automate_child_process.c \
		error_utils.c \
		child_processes.c \

CC = gcc
CCFLAG = -Wall -Werror -Wextra -g
# -fsanitize=address
#-g -fprofile-instr-generate -fcoverage-mapping
# MLXFLAGS =
LIB = -C ./libft
# GET = -C ./Get_next_line/
# ./Get_next_line/get_next_line_bonus.a

SUCCESS_COLOR = \033[32m

OBJECT = $(SRCS:.c=.o)
D_SRCS = ./srcs/

all : $(NAME)

%.o:$(D_SRCS)%.c
	$(CC) $(CCFLAG) -o $@ -c $<

$(NAME) : $(OBJECT)
	make $(LIB) >/dev/null 2>&1
	$(CC) $(CCFLAG) -g $(MLXFLAGS)  $(OBJECT) ./libft/libft.a -o $(NAME) >/dev/null 2>&1
	echo "$(SUCCESS_COLOR)$(NAME) - Compiled with Success"

clean :
	@make clean $(LIB) >/dev/null 2>&1
	@echo "$(SUCCESS_COLOR)$(NAME) - Cleaned with Success"
	@/bin/rm -rf $(OBJECT) >/dev/null 2>&1

fclean : clean
	@make fclean $(LIB) >/dev/null 2>&1
	@rm -rf ./$(NAME) >/dev/null 2>&1
	@echo "$(SUCCESS_COLOR)$(NAME) - FCleaned with Success"

re : fclean all

.PHONY: all clean fclean re
