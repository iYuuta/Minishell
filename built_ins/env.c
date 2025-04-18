#include "../minishell.h"

int   print_env(t_env *env)
{
    while (env)
    {
        if (ft_strlen(env->name) > 0 && env->arg && ft_strlen(env->arg) > 0)
            printf("%s=%s\n", env->name, env->arg);
        env = env->next;
    }
    return (0);
}