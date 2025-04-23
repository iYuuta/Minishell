#include "../minishell.h"

int skip_heredoc(char *str)
{
    int i;

    i = 0;
    if (str[i++] == '<' && str[i] == '<')
    {
        if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        {
            while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
                i++;
        }
        while (str[i] && str[i] != ' ' && (str[i] < 9 || str[i] > 13))
            i++;
    }
    return (i);
}

int skip_chars(char *str)
{
    int i;

    i = 1;
    while (str && (ft_isalnum(str[i]) || str[i] == '_'))
        i++;
    return (i);
}

char *expand_str(char *str, t_env *env, int *i, int skip)
{
    char *strings[4];
    t_env *variable;
    int j;

    j = -1;
    strings[3] = ft_strdup("");
    strings[0] = ft_substr(str, 0, *i);
    strings[1] = ft_substr(str, *i, skip);
    strings[2] = ft_substr(str, *i + skip, ft_strlen(str + (*i + skip)));
    if (str[*i + 1] && str[*i + 1] == '?')
        strings[1] = ft_itoa(return_value(0, 0));
    else
    {
        variable = get_env(env, strings[1] + 1);
        if (!variable)
            strings[1] = ft_strdup("");
        else
            strings[1] = variable->arg;
    }
    while (++j < 3)
        strings[3] = ft_strjoin(strings[3], strings[j]);
    *i = ft_strlen(strings[0]) + ft_strlen(strings[1]) - 1;
    return (strings[3]);
}

char *selective_expanding(t_env *env, char *str)
{
    int i;
    int flag;
    int skip;

    i = 0;
    flag = 2;
    while (str[i])
    {
        if (str[i] == '<')
            i += skip_heredoc(str + i);
        if (flag % 2 == 0 && str[i] && str[i] == '\'')
            i += get_index(str + i, '\'');
        else if (str[i] && str[i] == '\"')
            flag++;
        else if (str[i] && str[i] == '$' && str[i + 1] && !ft_strchr("%%^=+./", str[i + 1]))
        {
            skip = skip_chars(str + i);
            if (str[i + 1] && str[i + 1] == '?')
                skip = 2;
            str = expand_str(str, env, &i, skip);
        }
        i++;
    }
    return (str);
}

char *expand_vars(char *token, t_env *env)
{
    char *tmp;
    t_arg *var;
    int i;

    tmp = token;
    tmp = selective_expanding(env, tmp);
    return (tmp);
}
