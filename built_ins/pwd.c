#include "../minishell.h"

int pwd(t_env *env, t_cmd *cmd)
{
    char pwd[PATH_MAX];

    getcwd(pwd, PATH_MAX);
    if (!pwd[0])
        return (write(2, "error trying to fetch current working directory\n", 48), 1);
    ft_putendl_fd(pwd, cmd->outfile);
    return (0);
}
