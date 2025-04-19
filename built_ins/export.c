#include "../minishell.h"

int over_write(t_env *arg, char *value, int append)
{
    t_env *new;

    if (append)
    {
        if (!value)
            value = ft_env_strdup("");
        arg->arg = ft_env_join(arg->arg, value);
        if (!arg->arg)
            return (1);
        return (0);
    }
    arg->arg = ft_env_strdup(value);
    if (!arg->arg)
        return (1);
    return (0);
}

int add_env(t_env *arg, char *value, char *name)
{
    t_env *new;

    new = new_env(name);
    if (!new)
        return (1);
    new->arg = ft_env_strdup(value);
    env_add_back(&arg, new);
}

int export_w_args(t_arg *token, int append, int len)
{
    char *arg[2];

    if (len > 0 && token->token[len - 1] == '+')
            append = 1;
    arg[0] = ft_env_substr(token->token, 0, len - append);
    if (!arg[0])
        return (1);
    if (check_export_error(arg[0]))
        return (printf("bash: export: `%s': not a valid identifier\n", token->token), 1);
    if ((len + 1) != ft_strlen(token->token))
        arg[1] = ft_env_substr(token->token, len + 1, ft_strlen(token->token + len + 1));
    else
        arg[1] = ft_env_strdup("");
    if (!arg[1])
        return (1);
    if (!get_env(token->env, arg[0]))
        append = add_env(token->env, arg[1], arg[0]);
    else
        append = over_write(get_env(token->env, arg[0]), arg[1], append);
    if (append)
        return (1);
}

int export(t_arg *token)
{
    int len;
    int append;

    append = 0;
    if (!token->next)
        sort_export(token);
    token = token->next;
    while (token && token->type == WORD)
    {
        len = get_index(token->token, '=');
        if (len == -1)
        {
            if (!get_env(token->env, token->token))
                if (export_wt_args(token))
                    return (1);
        }
        else
            export_w_args(token, append, len);
        token = token->next;
    }
    return (0);
}
