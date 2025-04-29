#include "../minishell.h"

int	change_old_pwd(t_env *env, char *str)
{
	t_env	*oldpwd;

	oldpwd = get_env(env, "OLDPWD");
	if (!oldpwd)
		return (0);
	oldpwd->arg = ft_env_strdup(str);
	if (!oldpwd->arg)
		return (1);
	return (0);
}

t_env	*env_head(t_env *env)
{
	if (env && env->prev)
	{
		while (env->prev)
			env = env->prev;
	}
	return (env);
}
