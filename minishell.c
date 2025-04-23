#include "minishell.h"

char **oldenv(char **env)
{
	static char **envirement;

	if (env)
		envirement = env;
	return (envirement);
}

int return_value(int value, int flag)
{
    static int r_value;

    if (flag)
        r_value = value;
    return (r_value);
}

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
    static t_env *envirement;

    signal(SIGQUIT, handle_signales);
    signal(SIGINT, handle_signales);
    while (1)
    {
        if (return_value(0, 0) == 0)
            head_line = "\033[1;32m➜\033[0;34m  minishell>>\033[0m ";
        else
            head_line = "\033[0;31m➜\033[0;34m  minishell>>\033[0m ";
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

	oldenv(env);
    envirement = env_init(env);
    if (read_shell(envirement, "minishell>> ") == 1)
        return (1);
    return (0);
}
