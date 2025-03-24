SRC = minishell.c

helper = helper/ft_malloc.c helper/lst.c

signals = signals/signal.c

parsing = parsing/parse.c parsing/handle_quotes.c parsing/syntax_errors.c parsing/tokenize.c

OBJ = $(SRC:.c=.o) $(helper:.c=.o) $(parsing:.c=.o) $(signals:.c=.o)

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

helper/%.o : helper/%.c minishell.h
	cc $(CFLAGS) $(ReadLine) -c $< -o $@

signals/%.o : signals/%.c minishell.h
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