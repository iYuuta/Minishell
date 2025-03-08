SRC = minishell.c signal.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra

ReadLine = -lreadline

NAME = minishell

$(NAME) : $(OBJ)
	cc $(OBJ) $(ReadLine) -o $(NAME)

%.o : %.c minishell.h
	cc $(CFLAGS) $(ReadLine) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all