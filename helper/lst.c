#include "../minishell.h"

t_arg	*ft_lstnew(void *content)
{
	t_arg	*strc;

	strc = ft_malloc(sizeof(t_arg), 1);
	if (!strc)
		return (NULL);
	strc->token = content;
    strc->type = 1337;
	strc->head = NULL;
	strc->next = NULL;
	strc->prev = NULL;
	return (strc);
}

t_arg	*ft_lstlast(t_arg *lst)
{
	t_arg	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	ft_lstadd_back(t_arg **lst, t_arg *new)
{
	t_arg	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		(*lst)->next = NULL;
		new->head = new;
		return ;
	}
	temp = ft_lstlast(*lst);
	new->prev = temp;
	new->head = (*lst)->head;
	temp->next = new;
}

int	ft_lstsize(t_arg *lst)
{
	int		size;
	t_arg	*temp;

	size = 0;
	if (!lst)
		return (0);
	temp = lst;
	while (temp != NULL)
	{
		temp = temp->next;
		size++;
	}
	return (size);
}