#include "../minishell.h"

int	identify_tokens(t_arg *token)
{
	while (token)
	{
		if (is_redirection(token->token))
		{
			token->type = is_redirection(token->token);
			token = handle_redir(token);
		}
		else
			token->type = is_pipe(token->token);
		token = token->next;
	}
	return (0);
}

t_arg	*tokenize_arg(char **av, t_env *env)
{
	int		i;
	t_arg	*head;
	t_arg	*tmp;

	i = -1;
	head = NULL;
	while (av[++i])
	{
		tmp = ft_lstnew(av[i]);
		tmp->env = env;
		ft_lstadd_back(&head, tmp);
	}
	identify_tokens(head);
	return (head);
}
