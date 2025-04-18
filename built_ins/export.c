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

int check_error(char *str)
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
    if (!value)
        value = ft_env_strdup("");
    arg->arg = ft_env_strdup(value);
    if (!arg->arg)
        return (1);
    printf("%s=%s\n", arg->name, arg->arg);
    return (0);
}

int add_env(t_env *arg, char *value, char *name)
{
    t_env *new;

    new = new_env(name);
    if (!new)
        return (1);
    if (!value)
        value = ft_env_strdup("");
    new->arg = ft_env_strdup(value);
    printf("%s=%s\n", new->name, new->arg);
    env_add_back(&arg, new);
}

int export(t_arg *token)
{
    char *arg[2];
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
            len = ft_strlen(token->token);
        if (len > 0 && token->token[len - 1] == '+')
            append = 1;
        arg[0] = ft_env_substr(token->token, 0, len - append);
        if (!arg[0])
            return (1);
        if (check_error(arg[0]))
            return (printf("bash: export: `%s': not a valid identifier\n", token->token), 1);
        if (len == ft_strlen(token->token))
            arg[1] = NULL;
        else
            arg[1] = ft_env_substr(token->token, len + 1, ft_strlen(token->token + len + 1));
        if (!arg[1])
            return (1);
        if (!get_env(token->env, arg[0]))
            append = add_env(token->env, arg[1], arg[0]);
        else
            append = over_write(get_env(token->env, arg[0]), arg[1], append);
        if (append)
            return (1);
        token = token->next;
    }
    return (0);
}
