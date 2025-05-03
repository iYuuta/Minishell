#include "../minishell.h"

int *save_pid(int pid, int size, int flag)
{
	static int *pids;
	static int index;

	if (flag == 2)
	{
		pids = NULL;
		index = 0;
		return (NULL);
	}
	if (!pids)
	{
		pids = ft_malloc(sizeof(int) * (size + 1), 1);
		return (NULL);
	}
	if (flag)
		pids[index++] = pid;
	pids[index] = 0;
	return (pids);
}

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
