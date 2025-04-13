#include "../minishell.h"

int export(t_arg *arg)
{
    t_env *new;
    int len;

    while (arg && arg->type == WORD)
    {
        len = get_index(arg->token, '=');
        new = new_env(ft_env_substr(arg->token, 0, len));
        if (!new)
            return (1);
        new->arg = ft_env_substr(arg->token, len + 1, ft_strlen(arg->token + len + 1));
        // if (!new->arg)
        //     return (NULL);
        env_add_back(&arg->env, new);
        printf("%s->|%s|\n", new->name, new->arg);
        arg = arg->next;
    }
    return (0);
}