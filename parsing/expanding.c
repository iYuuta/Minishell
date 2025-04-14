#include "../minishell.h"

int skip_chars(char *str)
{
    int i;

    i = 1;
    while (str && !ft_strchr("\'\"$", str[i]))
        i++;
    return (i);
}

// int ft_get_index(char *str)
// {
//     int i;

//     i = 1;
//     if (ft_strchr("\'\"", *str))
//         return (get_index(str, *str) + 1);
//     while (str[i])
//     {
//         if (str[i] == '$')
//             return (i);
//         if (ft_strchr("\'\"", str[i]))
//             return (i);
//         i++;
//     }
//     return (i);
// }

// int count_words(char *str)
// {
//     int words;
//     int i;

//     words = 0;
//     i = 0;
//     while (str[i])
//     {
//         if (ft_strchr("\'\"", str[i]))
//         {
//             words++;
//             i = get_index(str + i, str[i]);
//         }
//         else if (str[i] == '$')
//         {
//             words++;
//             i = skip_chars(str + i);
//         }
//         else
//         {
//             words++;
//             while (str[i] && !ft_strchr("\'\"$", str[i]))
//                 i++;
//         }
//         i++;
//     }
//     return (words);
// }

// char **split_words(char *str)
// {
//     char **splitted_str;
//     int j;
//     int k;
//     int i;
    
//     i = 0;
//     k = 0;
//     j = count_words(str);
//     printf("%d\n", j);
//     splitted_str = (char **)ft_malloc(sizeof(char *) * (j + 1), 1);
//     if (!splitted_str)
//         return (NULL);
//     splitted_str[j] = 0;
//     while (str[i] && k < j)
//     {
//         splitted_str[k] = (char *)ft_substr(str, i, ft_get_index(str + i));
//         if (!splitted_str[k])
//             return (printf("%d\n", k), NULL);
//         i += ft_get_index(str + i);
//         k++;
//     }
//     return (splitted_str);
// }

// char *get_var(t_env *env, char *str)
// {
//     t_env *tmp;
//     char **idk;
//     char *expanded = NULL;
//     int i;

//     i = 0;
//     idk = split_words(str);
//     if (!idk)
//         return (write(1, "failed\n", 7), NULL);
//     while (idk[i])
//     {
//         if (idk[i][0] == '$' && idk[i][1])
//         {
//             tmp = env;
//             while (tmp)
//             {
//                 if (!ft_strcmp(idk[i] + 1, tmp->name))
//                     idk[i] = tmp->arg;
//                 tmp = tmp->next;
//             }
//             if (idk[i][0] == '$')
//                 idk[i] = ft_strdup("");
//             printf("%s\n", idk[i]);
//         }
//         i++;
//     }
//     i = 0;
//     expanded = idk[i];
//     while (idk[++i])
//         expanded = ft_strjoin(expanded, idk[i]);
//     return (expanded);
// }

char *expand(t_env *env, char *str)
{
    while (env)
    {
        if (!ft_strcmp(env->name, str))
            return (env->arg);
        env = env->next;
    }
    return (NULL);
}

char *selective_expanding(t_env *env, char *str)
{
    char *strings[3];
    char *new_str;
    int i;
    int len;
    int index;

    i = 0;
    while (str[i])
    {
        if (str[i] && str[i] == '\'')
            i += get_index(str + i, '\'');
        else if (str[i] && str[i] == '\"')
        {
            new_str = ft_strdup("");
            index = get_index(str, '$');
            strings[0] = ft_substr(str, 0, index);
            strings[1] = ft_substr(str, index, skip_chars(str + index));
            strings[2] = ft_substr(str, index + skip_chars(str + index), ft_strlen(str + (index + skip_chars(str + index))));
            strings[1] = expand(env, strings[1] + 1);
            for (int i = 0; i < 3; i++)
                new_str = ft_strjoin(new_str, strings[i]);
            str = new_str;
        }
        else if (str[i] && str[i] == '$')
        {
            new_str = ft_strdup("");
            strings[0] = ft_substr(str, 0, i);
            strings[1] = ft_substr(str, i, skip_chars(str + i));
            strings[2] = ft_substr(str, i + skip_chars(str + i), ft_strlen(str + (i + skip_chars(str + i))));
            strings[1] = expand(env, strings[1] + 1);
            for (int i = 0; i < 3; i++)
                new_str = ft_strjoin(new_str, strings[i]);
            str = new_str;
        }
        if (!str[i])
            break ;
        i++;
    }
    return (str);
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
            tmp->token = selective_expanding(token->env, tmp->token);
        }
        tmp = tmp->next;
    }
    return (token);
}
