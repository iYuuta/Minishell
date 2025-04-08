#include "../minishell.h"

//this is a grabage collector when ever u call 
//ft_malloc it does the same as regular malloc but it saves the allocate
//pointer so we can free it later on

void	stack_garbage(t_malloc **lst, t_malloc *new)
{
	t_malloc	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (*lst)
        *lst = (*lst)->next;
	temp->next = new;
}

void *ft_malloc(size_t size, int flag)
{
    static t_malloc *collector;
    t_malloc *tmp;
    void *ptr;

    if (!collector)
    {
        collector = malloc(sizeof(t_malloc));
        ptr = malloc(size);
        collector->ptr = ptr;
        collector->next = NULL;
        return (ptr);
    }
    if (!flag)
    {
        while (collector)
        {
            tmp = collector;
            collector = collector->next;
            free(tmp->ptr);
            free(tmp);
        }
        return (NULL);
    }
    tmp = malloc(sizeof(t_malloc));
    ptr = malloc(size);
    tmp->ptr = ptr;
    stack_garbage(&collector, tmp);
    return (ptr);
}
