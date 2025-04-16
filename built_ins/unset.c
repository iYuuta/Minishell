#include "../minishell.h"
t_env *env_head(t_env *env)
{
    if (env && env->prev)
    {
        while (env->prev)
            env = env->prev;
    }
    return (env);
}

t_env *remove_env(t_env *env)
{
    t_env *tmp;

    if (env && env->prev)
    {
        tmp = env->prev;
        tmp->next = env->next;
        return (env_head(tmp));
    }
    else if (env && env->next)
    {
        tmp = env->next;
        tmp->prev = NULL;
        return (env_head(tmp));
    }
	return (env_head(env));
}

void update_env(t_arg *head, t_env *env)
{
    while (head)
    {
        head->env = env;
        head = head->next;
    }
}

int unset(t_arg *arg)
{
    t_env *tmp;
    t_arg *head;

    head = arg;
    while (arg)
    {
        if (arg->type == PIPE)
            break ;
        if (arg->type == WORD)
        {
            tmp = arg->env;
            while (tmp)
            {
                if (!ft_strcmp(tmp->name, arg->token))
                {
                    arg->head->env = remove_env(tmp);
                    update_env(arg->head, arg->head->env);
					head = arg->head;
                }
                tmp = tmp->next;
            }
        }
        arg = arg->next;
    }
	change_env(head->env);
    return (0);
}
