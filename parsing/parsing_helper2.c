#include "../minishell.h"

int	is_ambiguous(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (!str[i])
		return (1);
	while (str[i] && str[i] != ' ' && (str[i] < 9 || str[i] > 13))
		i++;
	if (!str[i])
		return (0);
	return (1);
}

t_arg	*refine_token(t_arg *token)
{
	t_arg	*head;
	int		tracker;

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

int	check_files(t_arg *args)
{
	while (args)
	{
		if (args->type != WORD && args->prev && args->prev->type != HEREDOC
			&& ft_strchr(args->token, '$') && args->token[0] != '\"')
		{
			args->token = expand_vars(args->env, args->token, 0);
			if (!args->token || !args->token[0] || is_ambiguous(args->token))
				return (ft_putendl_fd("minishell: ambiguous redirect", 2), 1);
			args->token = ft_strtrim(args->token, " ");
		}
		else if (args->prev && args->prev->type != HEREDOC
			&& ft_strchr(args->token, '$'))
			args->token = expand_vars(args->env, args->token, 0);
		args = args->next;
	}
	return (0);
}

int	get_files(t_arg *token, t_cmd **node)
{
	t_file	*tmp;

	(*node)->file = NULL;
	if (check_files(token))
		return (1);
	while (token && token->type != PIPE)
	{
		if (token->type == REDIR_IN || token->type == REDIR_OUT
			|| token->type == REDIR_APPEND || token->type == HEREDOC)
		{
			tmp = ft_malloc(sizeof(t_file), 1);
			if (!tmp)
				return (1);
			tmp->type = token->type;
			tmp->file = token->next->token;
			if (tmp->type != HEREDOC)
				tmp->file = polish(tmp->file);
			if (tmp->type == HEREDOC)
				token = token->next;
			tmp->next = NULL;
			stack_files(&((*node)->file), tmp);
		}
		token = token->next;
	}
	return (0);
}
