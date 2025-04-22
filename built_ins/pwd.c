#include "../minishell.h"

int pwd(t_env *env, t_cmd *cmd)
{
    char pwd[PATH_MAX];
    t_env *back_up;

    if (getcwd(pwd, PATH_MAX))
        ft_putendl_fd(pwd, 1);
    else
    {
        back_up = get_env(env, "PWD");
        if (!back_up)
            return (1);
        ft_putendl_fd(back_up->arg, 1);
    }
    return (0);
}
