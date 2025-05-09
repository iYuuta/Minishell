#include "../minishell.h"

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
	remove_env(var);
	update_env(head->head, head->head->env);
	head = head->head;
	return (0);
}

static void	print_error(char *str)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	unset(t_arg *arg)
{
	t_env	*tmp;
	t_arg	*head;

	head = arg;
	return_value(0, 1);
	while (arg)
	{
		if (arg->type == WORD
			&& check_export_error(arg->token) && return_value(1, 1))
			print_error(arg->token);
		else if (arg->type == WORD)
		{
			tmp = head->env;
			while (tmp)
			{
				if (!ft_strcmp(arg->token, "PATH"))
					arg->head->env->arg = ft_env_strdup("");
				if (!ft_strcmp(tmp->name, arg->token))
					unset_var(head, tmp);
				tmp = tmp->next;
			}
		}
		arg = arg->next;
	}
	return (return_value(0, 0));
}
