# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/30 12:59:40 by ibaines           #+#    #+#              #
#    Updated: 2022/12/30 12:59:41 by ibaines          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= Minishell
CC= gcc
CFLAGS= -Wall -Wextra -Werror -g3
CFLAGS= 
SANITIZE= -fsanitize=address
RM= rm -rf
FILES= 	testeo \
		ft_strncmp \
		utils \
		pipes \
		pipe_com \
		pipe_com2 \
		signals \
		builtin \
		builtin2 \
		export \
		unset \
		built_utils \
		com_check \
		malloc_free \


LIBFT = libftt/libft.a

READLINE_DIR = ${HOME}/.brew/opt/readline

F_READLINE = -I$(READLINE_DIR)/include

COMPILE = -lreadline -L$(READLINE_DIR)/lib

SRC= $(addsuffix .c, $(FILES))
OBJ= $(addsuffix .o, $(FILES))

.c.o:
	$(CC) $(CFLAGS) $(F_READLINE) $(SANITIZE) -o $@ -c $^

$(NAME): $(OBJ) 
	${MAKE} -s -C libftt
	$(CC) $(CFLAGS) $(LIBFT) $(SANITIZE)  $(COMPILE) -o $(NAME) $(OBJ)

all: $(NAME)

clean: 
	${MAKE} clean -s -C libftt
	$(RM) $(OBJ)

fclean: clean
	${MAKE} fclean -s -C libftt
	$(RM) $(NAME)

re: fclean all

run:
	./$(NAME)

.PHONY:all clean fclean re


