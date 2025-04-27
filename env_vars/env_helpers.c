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
