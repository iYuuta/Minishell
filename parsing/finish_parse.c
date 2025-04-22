#include "../minishell.h"

t_cmd	*last_cmd(t_cmd *lst)
{
	t_cmd *temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	temp = last_cmd(*lst);
	temp->next = new;
}

int	count_cmds(t_arg *arg)
{
	int nb;

	nb = 1;
	while (arg)
	{
		if(arg->type == PIPE && arg->next != NULL)
			nb++;
		arg = arg->next;
	}
	return (nb);
}

void	stack_files(t_file **lst, t_file *new)
{
	t_file	*last_elem;

	if (!new || !lst)
		return ;
	last_elem = *lst;
	while (last_elem && last_elem->next)
		last_elem = last_elem->next;
	if (last_elem != NULL)
	{
		last_elem->next = new;
		return ;
	}
	*lst = new;
}

int get_files(t_arg *token, t_cmd **node)
{
	t_file *tmp;

	(*node)->file = NULL;
	while (token && token->type != PIPE)
	{
		if (token->type == REDIR_IN || token->type == REDIR_OUT || token->type == REDIR_APPEND || token->type == HEREDOC)
		{
			tmp = ft_malloc(sizeof(t_file), 1);
			if (!tmp)
				return (1);
			tmp->type = token->type;
			tmp->file = token->next->token;
			tmp->next = NULL;
			stack_files(&((*node)->file), tmp);
		}
		token = token->next;
	}
	return (0);
}

t_arg *copy_token(t_arg *token)
{
	t_arg *copy;

	copy = ft_malloc(sizeof(t_arg), 1);
	if (!copy)
		return (NULL);
	copy->head = NULL;
	copy->token = token->token;
	copy->type = token->type;
	copy->env = token->env;
	copy->next = NULL;
	copy->prev = NULL;
	return (copy);
}

t_arg *refine_token(t_arg *token)
{
	t_arg *head;
	int tracker;

	tracker = 0;
	head = token;
	if (token)
		token->type = CMD;
	token = token->next;
	while (token)
	{
		if (token->token[0] == '-' && token->token[1])
		{
			token->type = FLAG;
			tracker = 1;
		}
		else if (tracker)
			break ;
		token = token->next;
	}
	return (head);
}

t_cmd *get_cmd_arg(t_arg *token)
{
	t_cmd *node;
	t_arg *tmp;

	node = ft_malloc(sizeof(t_cmd), 1);
	if (!node)
		return (NULL);
	node->infile = 0;
	node->outfile = 1;
	node->tube[0] = -1;
	node->tokens = NULL;
	node->next = NULL;
	if (get_files(token, &node))
		return (NULL);
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
		{
			tmp = copy_token(token);
			if (!tmp)
				return (NULL);
			ft_lstadd_back(&(node->tokens), tmp);
		}
		token = token->next;
	}
	if (node->tokens)
		node->tokens = refine_token(node->tokens);
	return (node);
}

t_cmd *finish_parse(t_arg *args, t_env *env)
{
	int nb;
	t_cmd *head;
	t_cmd *tmp;

	head = NULL;
	nb = count_cmds(args);
	while (nb > 0)
	{
		tmp = get_cmd_arg(args);
		if (!tmp)
			return (NULL);
		tmp->env = env;
		cmd_add_back(&head, tmp);
		while (args && args->type != PIPE)
			args = args->next;
		if (args)
			args = args->next;
		nb--;
	}
	return (head);
}
