#include "../minishell.h"

int pwd(t_env *env, int fd)
{
    char *tmp;

    tmp = getcwd(NULL, 0);
    ft_putstr_fd(tmp, fd);
    free(tmp);
    return (0);
}
