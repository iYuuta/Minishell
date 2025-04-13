#include "../minishell.h"

int ft_get_index(char *str)
{
    int i;

    i = 1;
    if (ft_strchr("\'\"", *str))
        return (get_index(str, *str) + 1);
    while (str[i])
    {
        if (ft_strchr("$\'\"", str[i]))
            return (i);
        i++;
    }
    return (i);
}

int count_words(char *str)
{
    int words;
    int i;

    words = 1;
    i = 0;
    while (str[i])
    {
        while (str[i] && str[i] != '$')
            i++;
        if (str[i] && str[i++] == '$')
            words++;
        while (str[i] && ft_isalpha(str[i]))
            i++;
        if (str[i] && ft_strchr("?\'\"", str[i]) && str[++i])
            words++;
    }
    return (words);
}

char **split_words(char *str)
{
    char **splitted_str;
    int j;
    int k;
    int i;
    
    i = 0;
    k = 0;
    j = count_words(str);
    splitted_str = (char **)ft_malloc(sizeof(char *) * (j + 1), 1);
    if (!splitted_str)
        return (NULL);
    splitted_str[j] = 0;
    while (str[i] && k < j)
    {
        splitted_str[k] = (char *)ft_substr(str, i, ft_get_index(str + i));
        if (!splitted_str[k])
            return (printf("%d\n", k), NULL);
        i += ft_get_index(str + i);
        k++;
    }
    k = -1;
    while (++k < j)
        printf("%s\n", splitted_str[k]);
    return (splitted_str);
}

char *get_var(t_env *env, char *str)
{
    t_env *tmp;
    char **idk;
    char *expanded;
    int i;

    i = 0;
    idk = split_words(str);
    if (!idk)
        return (write(1, "failed\n", 7), NULL);
    printf("%s\n", NULL);
    for (int k = 0; k < count_words(str); k++)
        printf("%s\n", idk[k]);
    while (idk[i])
    {
        if (idk[i][0] == '$' && idk[i][1])
        {
            tmp = env;
            while (tmp)
            {
                if (!ft_strcmp(idk[i] + 1, tmp->name))
                    idk[i] = tmp->arg;
                tmp = tmp->next;
            }
            if (idk[i][0] == '$')
                idk[i] = ft_strdup("");
            printf("%s\n", idk[i]);
        }
        i++;
    }
    i = -1;
    while (idk[++i])
        expanded = ft_strjoin(expanded, idk[i]);
    return (expanded);
}

t_arg *expand_vars(t_arg *token)
{
    t_arg *tmp;
    t_arg *var;
    int i;

    tmp = token;
    while (tmp)
    {
        if (ft_strchr(tmp->token, '$'))
        {
            split_words(tmp->token);
            var->token = get_var(token->env, var->token);
        }
        tmp = tmp->next;
    }
    return (token);
}
