#include "../minishell.h"

int change_directory(t_arg *arg)
{
    if (chdir(arg->token))
        return (printf("bash: cd: %s: No such file or directory\n", arg->token), 1);
    return (0);
}