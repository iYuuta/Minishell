#include "../minishell.h"

void handle_signales(int signal)
{
    if (signal == SIGINT)
    {
        if (ctrl == 3)
            ioctl(STDIN_FILENO, TIOCSTI, "\n");
        ctrl = 1;
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        return_value(130, 1);
    }
    else if (signal == SIGQUIT)
    {
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}