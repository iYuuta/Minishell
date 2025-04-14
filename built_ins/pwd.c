#include "../minishell.h"

int pwd(t_env *env, int fd)
{
    char *tmp;

    tmp = getcwd(NULL, 0);
    if (!tmp)
        return (write(1, "error trying to fetch current working directory\n", 48), 0);
    ft_putendl_fd(tmp, fd);
    free(tmp);
    return (0);
}
