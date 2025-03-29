SRC = minishell.c

helper = helper/ft_malloc.c helper/lst.c

signals = signals/signal.c

parsing = parsing/parse.c parsing/handle_quotes.c parsing/syntax_errors.c parsing/tokenize.c parsing/here_doc.c

execution = execution/execute.c

OBJ = $(SRC:.c=.o) $(helper:.c=.o) $(parsing:.c=.o) $(signals:.c=.o) $(execution:.c=.o)

CFLAGS = -g -fsanitize=address

LIBFT = libft_dyali/libft.a

ReadLine = -lreadline

NAME = minishell

all : $(LIBFT) $(NAME)

$(LIBFT) :
	make -C libft_dyali

$(NAME) : $(OBJ)
	cc $(CFLAGS) $(OBJ) $(ReadLine) $(LIBFT) -o $(NAME)

parsing/%.o : parsing/%.c minishell.h
	cc $(CFLAGS) $(ReadLine) -c $< -o $@

execution/%.o : execution/%.c minishell.h
	cc $(CFLAGS) $(ReadLine) -c $< -o $@

helper/%.o : helper/%.c minishell.h
	cc $(CFLAGS) $(ReadLine) -c $< -o $@

signals/%.o : signals/%.c minishell.h
	cc $(CFLAGS) $(ReadLine) -c $< -o $@

%.o : %.c minishell.h
	cc $(CFLAGS) $(ReadLine) -c $< -o $@

clean:
	$(RM) $(OBJ)
	make -C libft_dyali clean

fclean: clean
	$(RM) $(NAME)
	make -C libft_dyali fclean

re : fclean all
