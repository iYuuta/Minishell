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

LIBFT_SRC = libft_dyali/ft_atoi.c libft_dyali/ft_bzero.c libft_dyali/ft_calloc.c libft_dyali/ft_isalnum.c \
	  libft_dyali/ft_isalpha.c libft_dyali/ft_isascii.c libft_dyali/ft_isdigit.c \
	  libft_dyali/ft_isprint.c libft_dyali/ft_itoa.c libft_dyali/ft_memchr.c libft_dyali/ft_strcmp.c \
	  libft_dyali/ft_memcmp.c libft_dyali/ft_memcpy.c libft_dyali/ft_memmove.c \
	  libft_dyali/ft_memset.c libft_dyali/ft_putchar_fd.c libft_dyali/ft_putendl_fd.c \
	  libft_dyali/ft_putstr_fd.c libft_dyali/ft_split.c libft_dyali/ft_strchr.c libft_dyali/ft_putnbr_fd.c \
	  libft_dyali/ft_strdup.c libft_dyali/ft_striteri.c libft_dyali/ft_strjoin.c \
	  libft_dyali/ft_strlcat.c libft_dyali/ft_strlcpy.c libft_dyali/ft_strlen.c \
	  libft_dyali/ft_strmapi.c libft_dyali/ft_strncmp.c libft_dyali/ft_strnstr.c \
	  libft_dyali/ft_strrchr.c libft_dyali/ft_strtrim.c libft_dyali/ft_substr.c \
	  libft_dyali/ft_tolower.c libft_dyali/ft_toupper.c 

OBJ = $(SRC:.c=.o) $(helper:.c=.o) $(parsing:.c=.o) $(signals:.c=.o) \
	$(execution:.c=.o) $(env_vars:.c=.o) $(built_ins:.c=.o) $(LIBFT_SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I$(shell brew --prefix readline)/include

ReadLine = -L$(shell brew --prefix readline)/lib -lreadline

NAME = minishell

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(CFLAGS) $(OBJ) $(ReadLine) $(LIBFT) -o $(NAME)

%.o : %.c minishell.h
	cc $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re : fclean all
