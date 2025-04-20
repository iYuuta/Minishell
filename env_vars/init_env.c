#include "../minishell.h"

t_env	*new_env(char *content)
{
	t_env	*strc;

    if (!content)
        return (NULL);
	strc = env_malloc(sizeof(t_env), 1);
	if (!strc)
		return (NULL);
	strc->name = ft_env_strdup(content);
	strc->next = NULL;
	strc->prev = NULL;
	return (strc);
}

t_env	*last_env(t_env *lst)
{
	t_env	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = last_env(*lst);
	new->prev = temp;
	temp->next = new;
}

t_env *add_to_env(t_env *env, char *var)
{
	t_env *new;
	char *value;
	int len;

	new = env_malloc(sizeof(t_env), 1);
	if (!new)
		return (NULL);
	len = get_index(var, '=');
	if (len == -1)
	{
		len = ft_strlen(var);
		value = NULL;
	}
	else
	{
		value = ft_env_substr(var, len + 1, ft_strlen(var + len + 1));
		if (!value)
			return (NULL);
	}
	new = new_env(ft_env_substr(var, 0, len));
	if (!new)
		return (NULL);
	new->arg = value;
	env_add_back(&env, new);
	return (env);
}

t_env *env_init(char **env)
{
    t_env *head;
    t_env *tmp;
    int i;
    int len;

    i = 0;
    head = NULL;
	if (!env || !(*env))
	{
		head = new_env("");
		head->arg = ft_env_strdup("");
		return (head);
	}
    while (env[i])
    {
        len = get_index(env[i], '=');
		tmp = new_env(ft_env_substr(env[i], 0, len));
    	if (!tmp)
        	return (NULL);
		if ((len + 1) == ft_strlen(env[i]))
		{
			tmp->arg = ft_env_strdup("");
			if (!tmp->arg)
				return (NULL);
		}
		else
		{
        	tmp->arg = ft_env_substr(env[i], len + 1, ft_strlen(env[i] + len + 1));
        	if (!tmp->arg)
        	    return (NULL);
		}
        env_add_back(&head, tmp);
        i++;
    }
    return (head);
}
