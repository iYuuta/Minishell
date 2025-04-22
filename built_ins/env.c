#include "../minishell.h"

int   print_env(t_env *env, t_cmd *cmd)
{
    while (env)
    {
        if (ft_strlen(env->name) > 0 && env->arg && ft_strlen(env->arg) > 0)
		{
			ft_putstr_fd(env->name, cmd->outfile);
			ft_putstr_fd("=", cmd->outfile);
			ft_putendl_fd(env->arg, cmd->outfile);
		}
        env = env->next;
    }
    return (0);
}
