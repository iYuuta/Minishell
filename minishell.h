#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

/************** signals **************/
void	handle_signales(int signal);
/*************************************/

/************** parsing **************/
int read_shell(void);
/*************************************/

#endif