#include "../minishell.h"

int g_ctrl;

void handle_signales(int signal)
{
    if (signal == SIGINT)
    {
        ft_putendl_fd("", STDOUT_FILENO);
        
        rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
        return_value(130, 1);
        if (g_ctrl == 3)
        {
            ioctl(STDIN_FILENO, TIOCSTI, "\n");
            g_ctrl = 1;
        }
        close_files(0, 0);
    }
    else if (signal == SIGQUIT)
    {
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}