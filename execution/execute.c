#include "../minishell.h"

char *ctf(t_arg *arg)
{
    char *flags;

    flags = ft_strdup("-");
    while (arg && arg->type != PIPE)
    {
        if (arg->type == FLAG)
            flags = ft_strjoin(flags, ft_strtrim(arg->token, "-"));
        arg = arg->next;
    }
    if (ft_strlen(flags) > 1)
        return (flags);
    return (NULL);
}

t_arg *get_cmd(t_arg *arg)
{
    while (arg)
    {
        if (arg->type == CMD)
            return (arg);
        arg = arg->next;
    }
    return (arg);
}

char **get_args(t_arg *arg)
{
    t_arg *tmp;
    int size;
    int i;
    char **str;

    i = 0;
    size = 0;
    tmp = arg;
    while (tmp && tmp->type != PIPE)
    {
        size++;
        tmp = tmp->next;
    }
    str = ft_malloc((size + 1) * sizeof(char *), 1);
    arg = get_cmd(arg->head);
    str[i++] = ft_strjoin("/usr/bin/", arg->token);
    if (size > 1)
    {
        str[i] = ctf(arg->head);
        if (str[i])
            i++;
        while (i < size && arg)
        {
            if (arg->type == WORD)
                str[i++] = arg->token;
            arg = arg->next;
        }
    }
    str[i] = NULL;
    return (str);
}

void execute_command(t_arg *arg)
{
    char **args;
    int i = 0;
    
    args = get_args(arg);
    // while (args[i])
    //     printf("%s\n", args[i++]);
    if (execv(args[0], args) == -1)
    {
        printf("%s: command not found\n", (get_cmd(arg))->token);
        ft_malloc(0, 0);
        exit(1);
    }
}

int check_builtins(t_arg *token)
{
    if (!ft_strcmp(token->token, "env"))
        return (print_env(token->env));
    if (!ft_strcmp(token->token, "pwd"))
        return (pwd(token->env, 1));
    if (!ft_strcmp(token->token, "unset"))
        return (unset(token), 0);
    if (!ft_strcmp(token->token, "export"))
        return (export(token->next));
    return (1);
}

int execution(char *str, t_env *env)
{
    t_arg *arg;

    arg = parse_args(str, env);
    if (!arg)
        return (1);
    if (!check_builtins(arg))
        return (0);
    execute_command(arg);
    return (0);
}