#include "../minishell.h"

void handle_signales(int signal)
{
    if (signal == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    else if (signal == SIGQUIT)
    {
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    else if (signal == EOF)
    {
        printf("\n");
        exit(0);
    }
}