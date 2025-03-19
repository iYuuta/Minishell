#include "minishell.h"

int read_shell(char **env, char *head_line)
{
    char *str;
    char **tmp;
    static char **idk;
    int i;

    i = 0;
    if (!idk)
        idk = env;
    while (1)
    {
        str = readline(head_line);
        if (!str)
           return 0;
        if (str[0] == '\\')
                read_shell(env, "> ");
        else if (str[0] == 'q')
            exit (0);
        else
            parse_args(str);
        free(str);
    }
}
int main(int ac, char **av, char **env)
{
    signal(SIGQUIT, handle_signales);
    signal(SIGINT, handle_signales);
    if (read_shell(env, "\033[1;34mminishell >> \033[0m") == 1)
        return (1);
    return (0);
}