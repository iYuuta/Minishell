#include "../minishell.h"

t_env *get_env(t_env *env, char *name)
{
    while (env)
    {
        if (!ft_strcmp(env->name, name))
            return (env);
        env = env->next;
    }
    return (NULL);
}

int check_export_error(char *str)
{
    if (*str != '_' && !ft_isalpha(*str))
        return (1);
    while (*str)
    {
        if (*str != '_' && !ft_isalnum(*str))
            return (1);
        str++;
    }
    return (0);
}

int export_wt_args(t_arg *arg)
{
    t_env *new;
    t_env *head;

    if (check_export_error(arg->token))
        return (printf("bash: export: `%s': not a valid identifier\n", arg->token), 1);
    head = arg->env;
    new = new_env(arg->token);
    if (!new)
        return (1);
    new->arg = NULL;
    new->next = NULL;
    env_add_back(&head, new);
    return (0);
}