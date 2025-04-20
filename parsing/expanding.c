#include "../minishell.h"

int skip_heredoc(char *str)
{
    int i;

    i = 0;
    if (str[i++] == '<' && str[i] == '<')
    {
        while (str[i] && str[i] != ' ')
            i++;
    }
    return (i);
}
int skip_chars(char *str)
{
    int i;

    i = 1;
    while (str && !ft_strchr("\'\"$", str[i]))
        i++;
    return (i);
}

char *expand(t_env *env, char *str)
{
    while (env)
    {
        if (!ft_strcmp(env->name, str))
        {
            if (!env->arg)
                return (ft_strdup(""));
            return (env->arg);
        }
        env = env->next;
    }
    return (ft_strdup(""));
}

char *selective_expanding(t_env *env, char *str)
{
    char *strings[4];
    int i;
    int flag;
    int index;

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
        else if (str[i] && str[i] == '$')
        {
            strings[3] = ft_strdup("");
            strings[0] = ft_substr(str, 0, i);
            strings[1] = ft_substr(str, i, skip_chars(str + i));
            strings[2] = ft_substr(str, i + skip_chars(str + i), ft_strlen(str + (i + skip_chars(str + i))));
            strings[1] = expand(env, strings[1] + 1);
            for (int k = 0; k < 3; k++)
                strings[3] = ft_strjoin(strings[3], strings[k]);
            str = strings[3]; 
            if (!strings[1][0])
                i--;
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
