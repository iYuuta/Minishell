#include "../minishell.h"

int get_index(char *str, char c)
{
    int i = 1;

    while (str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (-1);
}

char **split_args(char *str, int *size)
{
    int i;
    int j;
    int tmp;
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
                if (ft_strchr("\'\"", str[i + j]) && get_index(str + i + j, str[i + j]) == -1)
                {
                    printf("minishell: syntax error: unclosed quote\n");
                    ft_malloc(0, 0);
                    exit(1);
                }
                if (ft_strchr("\'\"", str[i + j]))
                    j += get_index(str + i + j, str[i + j]) + 1;
                else
                    j++;
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
