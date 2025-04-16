#include "../minishell.h"

//this is a grabage collector when ever u call 
//ft_malloc it does the same as regular malloc but it saves the allocate
//pointer so we can free it later on

void stack_garbage(t_malloc **lst, t_malloc *new)
{
    t_malloc *temp;

    if (!lst || !new)
        return;
    if (!*lst)
    {
        *lst = new;
        return;
    }
    temp = *lst;
    while (temp->next)
        temp = temp->next;
    temp->next = new;
}

void *ft_malloc(size_t size, int flag)
{
    static t_malloc *collector;
    t_malloc *tmp;

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
    if (!tmp)
        return (printf("ft_malloc failed\n"), NULL);
    tmp->ptr = malloc(size);
    if (!tmp->ptr)
    {
        free(tmp);
        return (printf("ft_malloc failed\n"), NULL);
    }
    tmp->next = NULL;
    return (stack_garbage(&collector, tmp), tmp->ptr);
}
