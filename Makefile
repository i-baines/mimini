NAME= Minishell
CC= gcc
CFLAGS= -Wall -Wextra -Werror -g3
CFLAGS= 
SANITIZE= -fsanitize=address
RM= rm -rf
FILES= 	testeo \
		ft_strncmp \
		utils

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


