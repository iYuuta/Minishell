#include "../minishell.h"

int pwd(t_env *env)
{
    char pwd[PATH_MAX];

    getcwd(pwd, PATH_MAX);
    if (!pwd)
        return (write(2, "error trying to fetch current working directory\n", 48), 1);
    ft_putendl_fd(pwd, 1);
    return (0);
}
