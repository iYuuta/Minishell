#include "../minishell.h"

char	*store_pwd(char *pwd)
{
	static char	*oldpwd;

	if (!oldpwd)
	{
		oldpwd = env_malloc(PATH_MAX, 1);
		if (!getcwd(oldpwd, PATH_MAX))
			oldpwd = NULL;
	}
	if (pwd)
		oldpwd = ft_env_strdup(pwd);
	return (oldpwd);
}

char	**oldenv(char **env)
{
	static char	**envirement;

	if (env)
		envirement = env;
	return (envirement);
}

int	return_value(int value, int flag)
{
	static int	r_value;
	if (flag)
		r_value = value;
	return (r_value);
}
