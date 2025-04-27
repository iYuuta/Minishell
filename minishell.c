#include "minishell.h"

char *store_pwd(char *pwd)
{
	static char *oldpwd;

    if (!oldpwd)
    {
        oldpwd = env_malloc(PATH_MAX, 1);
        getcwd(oldpwd, PATH_MAX);
    }
	if (pwd)
        oldpwd = ft_env_strdup(pwd);
    return (oldpwd);
}

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


int read_shell(t_env *env, char *head_line)
{
    char *str;

    signal(SIGQUIT, handle_signales);
    signal(SIGINT, handle_signales);
    while (1)
    {
        str = readline(head_line);
        if (!str)
        {
            env_malloc(0, 0);
            ft_putendl_fd("exit", 2);
            exit(0);
        }
        if (*str)
        {
            add_history(str);
            execution(str, env);
        }
        free(str);
        ft_malloc(0, 0);
    }
}

int main(int ac, char **av, char **env)
{
    t_env *envirement;

	oldenv(env);
    store_pwd(NULL);
    envirement = env_init(env);
    if (read_shell(envirement, "minishell>> ") == 1)
        return (1);
    return (0);
}
