#include "../minishell.h"

char *get_var(t_env *env, char *str)
{
    while (env)
    {
        if (!ft_strcmp(env->name, str))
            return (env->arg);
        env = env->next;
    }
    return (ft_strdup(""));
}

t_arg *expand_vars(t_arg *token)
{
    t_arg *tmp;
    t_arg *var;
    int i;

    i = 0;
    tmp = token;
    while (tmp)
    {
        if (tmp->type == VARIABLE)
        {
            var = tmp->next;
            tmp->prev->next = tmp->next;
            var->token = get_var(token->env, var->token);
        }
        tmp = tmp->next;
    }
    return (token);
}