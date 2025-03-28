#include "../minishell.h"

t_arg *read_here_doc(t_arg *token)
{
    char *stop;
    char *str;
    char *tmp;

    stop = token->token;
    str = ft_strdup("");
    tmp = NULL;
    while (1)
    {
        tmp = readline(">");
        if (!tmp)
            return (token);
        if (!strcmp(tmp, stop))
        {
            token->type = WORD;
            token->token = str;
            free(tmp);
            return (token);
        }
        str = ft_strjoin(str, tmp);
        free(tmp);
    }
    return (NULL);
}
