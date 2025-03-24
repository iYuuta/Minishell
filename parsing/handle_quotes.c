#include "../minishell.h"

int get_index(char *str, char c, char d)
{
    int i = 1;
    int nested_index;

    while (str[i])
    {
        if (str[i] == d)
        {
            nested_index = get_index(str + i, d, c);
            if (nested_index == -1)
                return -1;
            i += nested_index;
        }
        if (str[i] == c)
            return (i);
        i++;
    }
    return (-1);
}

int ft_get_quote(char *str, char c)
{
    int j;
    char tmp;

    tmp = (c == '\'') ? '"' : '\'';
    j = get_index(str, c, tmp);
    if (j == -1)
        return (-1);
    j++;
    while (str[j] && ft_strchr("\'\"", str[j]))
        j += ft_get_quote(str + j, str[j]);
    while (str[j] && !ft_strchr(" <>|&$", str[j]))
        j++;
    return (j);
}

char **split_args(char *str, int *size)
{
    int i;
    int j;
    char **args;
    char *arg;

    i = 0;
    j = 0;
    args = (char **)ft_malloc(sizeof(char *) * 100, 1);
    while (str[i])
    {
        j = 0;
        while (str[i] == ' ')
            i++;
        if (!str[i])
            break ;
        if (ft_strchr("<>|&$", str[i]))
        {
            j = 1;
            if (str[i + 1] && ft_strchr("<>|&$", str[i + 1]))
                j = 2;
        }
        else
        {
            while (str[i + j] && !ft_strchr(" <>|&$", str[i + j]))
            {
                if (str[i + j] == '\'' || str[i + j] == '\"')
                    j = ft_get_quote(str + i + j, str[i + j]) + 1;
                else
                    j++;
               if (j == -1)
               {
                    printf("minishell: syntax error: unclosed quote\n");
                    ft_malloc(0, 0);
                    exit(1);
                }
            }
        }
        arg = ft_substr(str, i, j);
        i += j;
        printf("|%s|\n", arg);
        args[*size] = arg;
        *size += 1;
    }
    args[*size] = NULL;
    return (args);
}
