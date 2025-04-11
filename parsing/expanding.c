#include "../minishell.h"

char *get_var(t_env *env, char *str)
{
    while (env)
    {
        if (ft_strncmp(env->name, str, ft_strlen(str)) == 0)
            return (env->arg);
        env = env->next;
    }
    return (ft_strdup(""));
}

t_arg *expand_vars(t_arg *token)
{
    t_arg *tmp;

    tmp = token;
    while (tmp)
    {
        if (tmp->type == VARIABLE)
        {
            printf("prev->%s curr->%s  next->%s\n", tmp->prev->token, tmp->token, token->next->token);
            tmp->prev->next = tmp->next;
            tmp = tmp->next;
            tmp->token = get_var(tmp->env, tmp->token);
            printf("|%s|\n", tmp->token);
        }
        tmp = tmp->next;
    }
    return (token);
}