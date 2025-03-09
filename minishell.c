#include "minishell.h"

int read_shell(char **env)
{
    char *str;
    static char **tmp;
    int i;

    if (!tmp)
        tmp = env;
    while (1)
    {
        str = readline("\033[1;34mminishell >> \033[0m");
        if (!str)
           return 0;
        if (str[0] == 'e' && str[1] == 'n' && str[2] == 'v')
        {
            i = 0;
            while (tmp[i])
                printf("%s\n", tmp[i++]);
        }
        else if (str[0] == '\n')
            printf("%s", str);
        else if (str[0] == 'q')
            exit (0);
        else
            printf("%s\n", str);
        free(str);
    }
}
int main(int ac, char **av, char **env)
{
    signal(SIGQUIT, handle_signales);
    signal(SIGINT, handle_signales);
    if (read_shell(env) == 1)
        return (1);
    return (0);
}