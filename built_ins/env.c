#include "../minishell.h"

int   print_env(t_env *env)
{
    while (env)
    {
        printf("%s=%s\n", env->name, env->arg);
        env = env->next;
    }
    return (0);
}