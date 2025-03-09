#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_env
{
    char *env;
    struct s_env *next;
}           t_env;

typedef struct s_arg
{
    char *arg;
    int type;
    struct s_arg *next;
}           t_arg;

/************** signals **************/

void	handle_signales(int signal);

/*************************************/

/************** parsing **************/

int read_shell(char **env);

/*************************************/

/************** helper ***************/

void *ft_malloc(size_t size, int flag);

/*********************************** */


#endif