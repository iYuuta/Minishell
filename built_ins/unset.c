#include "../minishell.h"

t_env	*env_head(t_env *env)
{
	if (env && env->prev)
	{
		while (env->prev)
			env = env->prev;
	}
	return (env);
}

t_env	*remove_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return (NULL);
	if (env->prev)
	{
		tmp = env->prev;
		tmp->next = env->next;
		if (env->next)
			env->next->prev = tmp;
		return (env);
	}
	else if (env->next)
	{
		tmp = env->next;
		tmp->prev = NULL;
		return (env);
	}
	return (NULL);
}

void	update_env(t_arg *head, t_env *env)
{
	while (head)
	{
		head->env = env;
		head = head->next;
	}
}

t_arg	*unset_var(t_arg *head, t_env *var)
{
	head->env = remove_env(var);
	update_env(head->head, head->head->env);
	head = head->head;
	return (0);
}

int	unset(t_arg *arg)
{
	t_env	*tmp;
	t_arg	*head;

	head = arg;
	while (arg)
	{
		if (arg->type == WORD)
		{
			tmp = arg->env;
			while (tmp)
			{
				if (ft_strcmp(tmp->name, "PATH"))
					arg->head->env->arg = ft_env_strdup("");
				if (!ft_strcmp(tmp->name, arg->token))
				{
					unset_var(head, tmp);
					break ;
				}
				tmp = tmp->next;
			}
		}
		arg = arg->next;
	}
	return (0);
}
