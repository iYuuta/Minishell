#include "minishell.h"

int read_shell(char **env, char *head_line)
{
    char *str;
    int child_pid;

    while (1)
    {
        str = readline(head_line);
        if (!str)
           return 0;
        if (*str)
        {
            add_history(str);
            child_pid = fork();
            if (child_pid == 0)
                execution(str);
            else
                waitpid(child_pid, NULL, 0);
        }
        free(str);
        ft_malloc(0, 0);
    }
}
int main(int ac, char **av, char **env)
{
    signal(SIGQUIT, handle_signales);
    signal(SIGINT, handle_signales);
    signal(EOF, handle_signales);
    if (read_shell(env, "\033[1;34mminishell>> \033[0m") == 1)
        return (1);
    return (0);
}
