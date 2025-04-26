#include "../minishell.h"

t_env *get_env(t_env *env, char *name)
{
    while (env)
    {
        if (!ft_strcmp(env->name, name))
            return (env);
        env = env->next;
    }
    if (env && !ft_strcmp(env->name, name))
        return (env);
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

static void printf_error(char *str)
{
    ft_putstr_fd("minishell: export: `", 2);
    ft_putstr_fd(str, 2);
    ft_putendl_fd("': not a valid identifier", 2);
}

int export_wt_args(t_cmd *arg)
{
    t_env *new;
    t_env *head;

    if (check_export_error(arg->tokens->token))
        return (printf_error(arg->tokens->token), 1);
    head = arg->env;
    new = new_env(arg->tokens->token);
    new->arg = NULL;
    new->next = NULL;
    env_add_back(&head, new);
    return (0);
}
