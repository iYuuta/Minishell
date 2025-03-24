#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#define fail 1
#define success 0



typedef enum e_token_type
{
    WORD,
    CMD,
    file,
    FLAG,
    PIPE,
    REDIR_OUT,
    REDIR_APPEND,
    REDIR_IN,
    HEREDOC,
    DQUOTE_STRING,
    SQUOTE_STRING,
    VARIABLE,
    LOGICAL_AND,
    LOGICAL_OR,
    BACKGROUND,
}   t_token_type;

typedef struct s_env
{
    char *env;
    struct s_env *next;
}           t_env;

typedef struct s_arg
{
    char *token;
    int  type;
    struct s_arg *next;
    struct s_arg *head;
    struct s_arg *branch;
}           t_arg;

/************** signals **************/

void	handle_signales(int signal);

/*************************************/

/************** parsing **************/

t_arg *parse_args(char *str);
int is_operator(char *str);
int is_flag(char *str);
char **split_args(char *str, int *size);
void polish(t_arg *token);
t_arg *tokenize_arg(char **av);

int ft_get_quote(char *str, char c);

/*************************************/

/************** helper ***************/

void *ft_malloc(size_t size, int flag);
t_arg	*ft_lstnew(void *content);
void	ft_lstadd_back(t_arg **lst, t_arg *new);
int	ft_lstsize(t_arg *lst);

/*********************************** */


#endif