#include "../minishell.h"

t_cmd	*lstlast(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last_elem;

	if (!new || !lst)
		return ;
	last_elem = *lst;
	if (last_elem != NULL)
	{
		last_elem = lstlast(last_elem);
		last_elem->next = new;
		return ;
	}
	*lst = new;
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


int	init_commands(t_arg *arg, t_cmd **cmds_head)
{
	int nb;
	t_cmd *element;

	nb = count_cmds(arg);
	while (nb > 0)
	{
		element = ft_malloc(sizeof(t_cmd), 1);
		element->cmd = NULL;
		element->cmd_args = NULL;
		element->infile = 0;
		element->outfile = 1;
		element->outfile_red = -1;
		while (arg != NULL && arg->type != PIPE)
		{
			if (arg->type == CMD)
				element->cmd = arg->token;
			arg = arg->next;
		}
		lstadd_back(cmds_head, element);
		nb--;
	}
	return (count_cmds(arg));
}