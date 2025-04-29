#include "../minishell.h"

t_env	*ft_envdup(t_env *env)
{
	t_env	*new;

	new = ft_malloc(sizeof(t_env), 1);
	new->next = NULL;
	new->name = ft_strdup(env->name);
	if (!env->arg)
		new->arg = NULL;
	else
		new->arg = ft_strdup(env->arg);
	return (new);
}

int	ft_lst_contains(t_env *list, t_env *node)
{
	while (list)
	{
		if (list == node)
			return (1);
		list = list->next;
	}
	return (0);
}

int	ft_lst_contains_name(t_env *list, char *name)
{
	while (list)
	{
		if (ft_strcmp(list->name, name) == 0)
			return (1);
		list = list->next;
	}
	return (0);
}

t_env	*brute_sort(t_env *env)
{
	t_env	*tmp;
	t_env	*biggest;
	t_env	*new;
	t_env	*visited;

	new = NULL;
	visited = NULL;
	while (1)
	{
		tmp = env;
		biggest = NULL;
		while (tmp)
		{
			if (!ft_lst_contains_name(visited, tmp->name)
				&& (!biggest || ft_strcmp(tmp->name, biggest->name) < 0))
				biggest = tmp;
			tmp = tmp->next;
		}
		if (!biggest)
			break ;
		env_add_back(&new, ft_envdup(biggest));
		env_add_back(&visited, ft_envdup(biggest));
	}
	return (new);
}

int	sort_export(t_cmd *cmd)
{
	t_env	*sorted_env;

	sorted_env = brute_sort(cmd->env);
	while (sorted_env)
	{
		if (sorted_env->name[0] && sorted_env->name[0] != '_')
		{
			ft_putstr_fd("declare -x ", cmd->outfile);
			ft_putstr_fd(sorted_env->name, cmd->outfile);
			if (sorted_env->arg)
			{
				ft_putstr_fd("=\"", cmd->outfile);
				ft_putstr_fd(sorted_env->arg, cmd->outfile);
				ft_putstr_fd("\"", cmd->outfile);
			}
			write(1, "\n", cmd->outfile);
		}
		sorted_env = sorted_env->next;
	}
	return (0);
}
