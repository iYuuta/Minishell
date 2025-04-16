#include "minishell.h"

t_env *change_env(t_env *env)
{
    static t_env *new_env;

    if (env)
    {
        new_env = env;
        return (env);
    }
    return (new_env); 
}

int read_shell(t_env *env, char *head_line)
{
    char *str;
    int child_pid;
    static t_env *envirement;

    signal(SIGQUIT, handle_signales);
    signal(SIGINT, handle_signales);
    while (1)
    {
        if (!envirement)
            envirement = change_env(env);
        else
            envirement = change_env(NULL);
        str = readline(head_line);
        if (!str)
        {
            env_malloc(0, 0);
            exit(0);
        }
        if (*str)
        {
            add_history(str);
            execution(str, envirement);
        }
        free(str);
        ft_malloc(0, 0);
    }
}

int main(int ac, char **av, char **env)
{
    t_env *envirement;

    envirement = env_init(env);
    if (read_shell(envirement, "\033[1;34mminishell>> \033[0m") == 1)
        return (1);
    return (0);
}
