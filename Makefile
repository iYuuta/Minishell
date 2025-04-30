SRC = minishell.c

helper = helper/ft_malloc.c helper/lst.c helper/env_malloc.c helper/export_helper1.c \
			helper/export_helper2.c helper/storage.c

signals = signals/signal.c

built_ins = built_ins/env.c  built_ins/pwd.c built_ins/unset.c built_ins/export.c built_ins/exit.c \
			built_ins/cd.c built_ins/echo.c built_ins/built_in_helper.c

env_vars = env_vars/init_env.c env_vars/ft_env_helper.c env_vars/env_helpers.c

parsing = parsing/parse.c parsing/handle_quotes.c parsing/tokenize.c parsing/here_doc.c \
		  parsing/expanding.c parsing/finish_parse.c parsing/polish_tokens.c parsing/here_doc_helper.c \
		  parsing/parsing_helper1.c parsing/parsing_helper2.c parsing/parsing_helper3.c

execution = execution/execute.c execution/execution_helper1.c execution/excev_args.c execution/execution_helper2.c

OBJ = $(SRC:.c=.o) $(helper:.c=.o) $(parsing:.c=.o) $(signals:.c=.o) \
	$(execution:.c=.o) $(env_vars:.c=.o) $(built_ins:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I$(shell brew --prefix readline)/include

ReadLine = -L$(shell brew --prefix readline)/lib -lreadline

LIBFT = libft_dyali/libft.a

NAME = minishell

all : $(LIBFT) $(NAME)

$(LIBFT) :
	make -C libft_dyali

$(NAME) : $(OBJ)
	cc $(CFLAGS) $(OBJ) $(ReadLine) $(LIBFT) -o $(NAME)

%.o : %.c minishell.h
	cc $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	make -C libft_dyali clean

fclean: clean
	$(RM) $(NAME)
	make -C libft_dyali fclean

re : fclean all
