#include "../minishell.h"

char	*get_str(int i)
{
	static char	*str;

	if (i == 3)
		str = getcwd(NULL, 0);
	if (i == 0)
		return ("");
	if (i == 1)
		return (DEF_PATH);
	if (i == 2)
		return ("PWD");
	if (i == 3)
		return (str);
	if (i == 4)
		return ("SHLVL");
	if (i == 5)
		return ("1");
	if (i == 6)
		return ("OLDPWD");
	if (i == 7)
		return (NULL);
	if (i == 8)
		return ("_");
	if (i == 9)
		return ("/usr/bin/env");
	return (NULL);
}

t_env	*uninitialized_env(void)
{
	int		i;
	t_env	*head;
	t_env	*tmp;

	i = 0;
	head = NULL;
	while (i < 10)
	{
		tmp = new_env(get_str(i));
		i++;
		tmp->arg = get_str(i);
		env_add_back(&head, tmp);
		i++;
	}
	return (head);
}

t_env	*add_to_env(t_env *env, char *var)
{
	t_env	*new;
	char	*value;
	int		len;

	new = env_malloc(sizeof(t_env), 1);
	len = get_index(var, '=');
	if (len == -1)
	{
		len = ft_strlen(var);
		value = NULL;
	}
	else
		value = ft_env_sub(var, len + 1, ft_strlen(var + len + 1));
	new = new_env(ft_env_sub(var, 0, len));
	new->arg = value;
	env_add_back(&env, new);
	return (env);
}

t_env	*env_init(char **env, t_env *head, int i)
{
	t_env	*tmp;
	int		len;

	if (!env || !(*env))
		return (uninitialized_env());
	else
	{
		head = new_env("");
		head->arg = ft_env_strdup(DEF_PATH);
	}
	while (env[i])
	{
		len = get_index(env[i], '=');
		tmp = new_env(ft_env_sub(env[i], 0, len));
		if ((len + 1) == (int)ft_strlen(env[i]))
			tmp->arg = ft_env_strdup("");
		else
			tmp->arg = ft_env_sub(env[i], len + 1, ft_strlen(env[i] + len + 1));
		env_add_back(&head, tmp);
		i++;
	}
	tmp = get_env(head, "SHLVL");
	if (tmp)
		tmp->arg = ft_itoa(ft_atoi(tmp->arg) + 1);
	
	return (head);
}
