SRC = minishell.c signal.c

helper = helper/ft_malloc.c helper/lst.c

parsing = parsing/parse.c parsing/what_is_it.c

OBJ = $(SRC:.c=.o) $(helper:.c=.o) $(parsing:.c=.o)

CFLAGS = 

LIBFT = libft/libft.a

ReadLine = -lreadline

NAME = minishell

all : $(LIBFT) $(NAME)

$(LIBFT) :
	make -C libft

$(NAME) : $(OBJ)
	cc $(CFLAGS) $(OBJ) $(ReadLine) $(LIBFT) -o $(NAME)

parsing/%.o : parsing/%.c minishell.h
	cc $(CFLAGS) $(ReadLine) -c $< -o $@

helper/%.o : helper/%.c minishell.hm
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