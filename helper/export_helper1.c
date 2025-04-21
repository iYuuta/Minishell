#include "../minishell.h"

t_env *ft_envdup(t_env *env)
{
    t_env *new;

    new = ft_malloc(sizeof(t_env), 1);
    if (!new)
        return (NULL);
    new->next = NULL;
    new->name = ft_strdup(env->name);
    if (!new->name)
        return (NULL);
    if (!env->arg)
        new->arg = NULL;
    else
    {
        new->arg = ft_strdup(env->arg);
        if (!new->arg)
            return (NULL);
    }
    return (new);
}

int ft_lst_contains(t_env *list, t_env *node)
{
    while (list)
    {
        if (list == node)
            return (1);
        list = list->next;
    }
    return (0);
}

int ft_lst_contains_name(t_env *list, char *name)
{
    while (list)
    {
        if (ft_strcmp(list->name, name) == 0)
            return (1);
        list = list->next;
    }
    return (0);
}

t_env *brute_sort(t_env *env)
{
    t_env *tmp;
    t_env *biggest;
    t_env *new;
    t_env *visited;

    new = NULL;
    visited = NULL;
    while (1)
    {
        tmp = env;
        biggest = NULL;
        while (tmp)
        {
            if (!ft_lst_contains_name(visited, tmp->name) && 
                (!biggest || ft_strcmp(tmp->name, biggest->name) < 0))
                biggest = tmp;
            tmp = tmp->next;
        }
        if (!biggest)
            break;
        env_add_back(&new, ft_envdup(biggest));
        env_add_back(&visited, ft_envdup(biggest));
    }
    return (new);
}

int sort_export(t_cmd *cmd)
{
    t_env *sorted_env;

    sorted_env = brute_sort(cmd->env);
    while (sorted_env)
    {
        if (sorted_env->name[0])
        {
            printf("declare -x %s", sorted_env->name);
            if (sorted_env->arg)
                printf("=\"%s\"", sorted_env->arg);
            printf("\n");
        }
        sorted_env = sorted_env->next;
    }
    return (0);
}