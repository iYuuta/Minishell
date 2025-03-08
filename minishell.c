#include "minishell.h"

int read_shell(void)
{
    char *str;

    while (1)
    {
        str = readline("\033[1;34mminishell >> \033[0m");
        if (str[0] == '\0')
            printf("%s", str);
        if (str[0] == 'q')
            exit (0);
        else
            printf("%s\n", str);
    }
}
int main(int ac, char **av, char **env)
{
    signal(SIGQUIT, handle_signales);
    signal(SIGINT, handle_signales);
    if (read_shell() == 1)
        return (1);
    return (0);
}