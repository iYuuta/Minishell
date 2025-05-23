#include "../minishell.h"

void	stack_env_garbage(t_malloc **lst, t_malloc *new)
{
	t_malloc	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	*env_malloc(size_t size, int flag)
{
	static t_malloc	*collector;
	t_malloc		*tmp;

	if (!flag)
	{
		while (collector)
		{
			tmp = collector;
			collector = collector->next;
			free(tmp->ptr);
			free(tmp);
		}
		close_files(0, 0);
		return (NULL);
	}
	tmp = malloc(sizeof(t_malloc));
	if (!tmp)
		return (ft_malloc(0, 0),
			ft_putendl_fd("malloc failed", 2), exit(1), NULL);
	tmp->ptr = malloc(size);
	if (!tmp->ptr)
		return (ft_malloc(0, 0),
			ft_putendl_fd("malloc failed", 2), exit(1), NULL);
	tmp->next = NULL;
	return (stack_env_garbage(&collector, tmp), tmp->ptr);
}
