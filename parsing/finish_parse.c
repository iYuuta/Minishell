#include "../minishell.h"

int	count_cmds(t_arg *arg)
{
	int	nb;

	nb = 1;
	while (arg)
	{
		if (arg->type == PIPE && arg->next != NULL)
			nb++;
		arg = arg->next;
	}
	return (nb);
}

t_arg	*expand_token(t_arg *token, char *str)
{
	char	**args;
	t_arg	*tmp;
	int		i;

	i = 0;
	str = expand_vars(token->env, str, 0);
	str = ft_strtrim(str, " ");
	args = ft_split(str, ' ');
	while (args[i])
	{
		args[i] = polish(args[i]);
		if (i == 0)
			token = ft_lstnew(args[i]);
		else
		{
			tmp = ft_lstnew(args[i]);
			ft_lstadd_back(&token, tmp);
		}
		i++;
	}
	return (token);
}

t_arg	*get_new_token(t_arg *token, int *i, int *flag)
{
	t_arg	*tmp;

	if (*i == 0 && !ft_strcmp(token->token, "export"))
	{
		(*i)++;
		(*flag) = 1;
	}
	tmp = copy_token(token);
	if (!(*flag) && !ft_strchr("\"\'", token->token[0])
		&& ft_strchr(token->token, '$'))
		tmp = expand_token(token, tmp->token);
	else if (!(*flag))
		tmp->token = polish(tmp->token);
	return (tmp);
}

t_cmd	*get_cmd_arg(t_arg *token)
{
	t_cmd		*node;
	t_arg		*tmp;
	static int	i;
	int			flag;

	flag = 0;
	node = new_cmd();
	if (get_files(token, &node))
		return (NULL);
	if (token && token->type == PIPE)
		return (node);
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
		{
			tmp = get_new_token(token, &i, &flag);
			ft_lstadd_back(&(node->tokens), tmp);
		}
		token = token->next;
	}
	if (node->tokens)
		node->tokens = refine_token(node->tokens);
	return (i = 0, node);
}

t_cmd	*finish_parse(t_arg *args, t_env *env)
{
	int		nb;
	int		i;
	t_cmd	*head;
	t_cmd	*tmp;

	i = 0;
	head = NULL;
	nb = count_cmds(args);
	save_pid(0, nb, 0);
	while (i < nb)
	{
		tmp = get_cmd_arg(args);
		if (!tmp)
			return (NULL);
		tmp->env = env;
		tmp->number = i + 1;
		cmd_add_back(&head, tmp);
		while (args && args->type != PIPE)
			args = args->next;
		if (args)
			args = args->next;
		i++;
	}
	return (head);
}
