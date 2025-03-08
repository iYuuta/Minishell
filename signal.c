#include "minishell.h"

void handle_signales(int signal)
{
    if (signal == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    else if (signal == SIGQUIT)
    {
        printf("\n");
    }
}