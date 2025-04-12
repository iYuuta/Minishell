#include "../minishell.h"

t_env	*new_env(char *content)
{
	t_env	*strc;

    if (!content)
        return (NULL);
	strc = env_malloc(sizeof(t_env), 1);
	if (!strc)
		return (NULL);
	strc->name = content;
	strc->next = NULL;
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
	temp->next = new;
}

t_env *add_to_env(t_env *env, char *var)
{
	t_env *new;
	int len;

	len = get_index(var, '=');
	new = env_malloc(sizeof(t_env), 1);
	new->name = new_env(ft_env_substr(var, 0, len));
	if (!new)
		return (NULL);
	new->arg = ft_env_substr(env, len + 1, ft_strlen(env + len + 1));
	// if (!new->arg)
	// 	return (NULL);
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
    while (env[i])
    {
        len = get_index(env[i], '=');
        tmp = new_env(ft_env_substr(env[i], 0, len));
        if (!tmp)
            return (NULL);
        tmp->arg = ft_env_substr(env[i], len + 1, ft_strlen(env[i] + len + 1));
        // if (!tmp->arg)
        //     return (NULL);
        env_add_back(&head, tmp);
        i++;
    }
    return (head);
}