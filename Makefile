SRC = minishell.c signal.c

helper = helper/ft_malloc.c

OBJ = $(SRC:.c=.o) $(helper:.c=.o)

CFLAGS = 

LIBFT = libft/libft.a

ReadLine = -lreadline

NAME = minishell

all : $(LIBFT) $(NAME)

$(LIBFT) :
	make -C libft

$(NAME) : $(OBJ)
	cc $(OBJ) $(ReadLine) $(LIBFT) -o $(NAME)

helper/%.o : helper/%.c minishell.h
	cc $(CFLAGS) $(ReadLine) -c $< -o $@

%.o : %.c minishell.h
	cc $(CFLAGS) $(ReadLine) -c $< -o $@

clean:
	$(RM) $(OBJ)
	make -C libft clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re : fclean all