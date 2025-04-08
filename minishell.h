#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include "libft_dyali/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

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
    VAR_ASSING,
    BACKGROUND,
}   t_token_type;

typedef struct s_malloc
{
    void *ptr;
    struct s_malloc *next;
}           t_malloc;


typedef struct s_env
{
    char *name;
    char *arg;
    struct s_env *next;
}           t_env;

typedef struct s_arg
{
    char *token;
    int  type;
    struct s_env *env;
    struct s_arg *next;
    struct s_arg *prev;
    struct s_arg *head;
}           t_arg;

/************** signals **************/

void	handle_signales(int signal);

/*************************************/

/************* execution *************/

int execution(char *str);

/*************************************/
/************** parsing **************/

t_arg *parse_args(char *str);
int is_operator(char *str);
int is_flag(char *str);
char **split_args(char *str, int *size);
void polish(t_arg *token);
t_arg *tokenize_arg(char **av);
t_arg *read_here_doc(t_arg *token);
int check_uncompleted_cmd(t_arg *token);
int is_redirection(char *str);
int get_index(char *str, char c);

/*************************************/

/************** envirement ***********/

t_env *env_innit(t_arg *arg);

/*************************************/

/************** helper ***************/

void *env_malloc(size_t size, int flag);
void *ft_malloc(size_t size, int flag);
void *env_malloc(size_t size, int flag);
t_arg	*ft_lstnew(void *content);
void	ft_lstadd_back(t_arg **lst, t_arg *new);
int	ft_lstsize(t_arg *lst);
t_arg	*ft_lstlast(t_arg *lst);

/*********************************** */


#endif