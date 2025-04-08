#include "../minishell.h"

void stack_env(t_env **lst, t_env *new)
{
    t_env *temp;

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

t_env *env_innit(t_arg *arg)
{
    static t_env *env;
    t_env *tmp;
    int index;

    index = get_index(arg->token, '=');
    if (!env)
    {
        env = env_malloc(sizeof(t_env), 1);
        if(!env)
            return (NULL);
        env->name = ft_substr(arg->token, 0, index);
        env->arg = ft_substr(arg->token, index + 1, ft_strlen(arg->token + index + 1));
    }
    else
    {
        tmp = env_malloc(sizeof(t_env), 1);
        if (!tmp)
            return (NULL);
        tmp->name = ft_substr(arg->token, 0, index);
        tmp->arg = ft_substr(arg->token, index + 1, ft_strlen(arg->token + index + 1));
        return (stack_env(&env, tmp), env);
    }
    if (arg->prev)
        arg->prev->next = arg->next;
    else
        arg->next->prev = NULL;
    return (env);
}