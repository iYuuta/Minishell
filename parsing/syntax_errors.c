#include "../minishell.h"

void polish(t_arg *token)
{
    char *new;
    char c;
    int i;
    int len;

    i = 0;while (token->token[i])
    {
        if (token->token[i] != '\'' && token->token[i] != '\"')
            len++;
        i++;
    }
    new = ft_malloc(len + 1, 1);
    if (!new)
        return ;
    i = 0;
    len = 0;
    while (token->token[i])
    {
        c = token->token[i];
        if (c == '\'' || c == '\"')
        {
            while (token->token[++i] && token->token[i] != c)
            {
                new[len] = token->token[i];
                len++;
            }
            if (!token->token[i])
                break ;
        }
        else
            new[len++] = token->token[i];
        i++;
    }
    new[len] = '\0';
    token->token = new;
}
