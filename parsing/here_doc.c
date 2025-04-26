#include "../minishell.h"

int skip_chars_heredoc(char *str)
{
    int i;

    i = 1;
    while (str && !ft_strchr(" \'\"$", str[i]))
        i++;
    return (i);
}

char *get_var_heredoc(t_env *env, char *str)
{
    while (env)
    {
        if (!ft_strcmp(env->name, str))
            return (ft_strdup(env->arg));
        env = env->next;
    }
    return (ft_strdup(""));
}

char *new_stop(char *str)
{
    char *new;
    char c;
    int i;
    int len;

    i = 0;
    while (str[i])
    {
        if (str[i] != '\'' && str[i] != '\"')
            len++;
        i++;
    }
    new = ft_malloc(len + 1, 1);
    if (!new)
        return (NULL);
    i = 0;
    len = 0;
    while (str[i])
    {
        c = str[i];
        if (c == '\'' || c == '\"')
        {
            while (str[++i] && str[i] != c)
            {
                new[len] = str[i];
                len++;
            }
            if (!str[i])
                break ;
        }
        else
            new[len++] = str[i];
        i++;
    }
    new[len] = '\0';
    return (new);
}

char *expand_heredoc(t_env *env, char *str)
{
    char *strings[4];
    int i;
    int index;
    int j;

    i = 0;
    while (str[i])
    {
        if (str[i] && str[i] == '$')
        {
            j = -1;
            strings[3] = ft_strdup("");
            strings[0] = ft_substr(str, 0, i);
            strings[1] = ft_substr(str, i, skip_chars_heredoc(str + i));
            strings[2] = ft_substr(str, i + skip_chars_heredoc(str + i), ft_strlen(str + (i + skip_chars_heredoc(str + i))));
            strings[1] = get_var_heredoc(env, strings[1] + 1);
            while (++j < 3)
                strings[3] = ft_strjoin(strings[3], strings[j]);
            str = strings[3];
        }
        if (!str[i])
            break ;
        i++;
    }
    return (str);
}

char *read_here_doc(char *token, t_env *env)
{
    char *stop;
    char *str;
    char *tmp[2];
    int flag;

    flag = 1;
    if (ft_strchr(token, '\'') || ft_strchr(token, '\"'))
        flag = 0;
    stop = polish(token);
    str = ft_strdup("");
    g_ctrl = 3;
    while (1)
    {
        tmp[0] = readline("> ");
        if (!tmp[0])
            return (ft_putendl_fd("bash: warning: here-document delimited by end-of-file", 2), token = str, token);
        if (g_ctrl == 1)
            return (free(tmp[0]), NULL);
        if (!ft_strcmp(tmp[0], stop))
            return (token = str, free(tmp[0]), token);
        if (flag)
            tmp[1] = expand_heredoc(env, tmp[0]);
        else
            tmp[1] = tmp[0];
        str = ft_strjoin(str, tmp[1]);
        str = ft_strjoin(str, "\n");
        free (tmp[0]);
    }
    return (NULL);
}
