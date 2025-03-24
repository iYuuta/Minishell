#include "../minishell.h"

int count_quotes(char *str, char impostor)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == impostor)
            count++;
        i++;
    }
    return (count);
}

void polish(t_arg *token)
{
    char *new;
    int i;
    int len;

    i = 0;
    if (count_quotes(token->token, '\'') % 2 != 0 || count_quotes(token->token, '\"') % 2 != 0)
    {
        printf("minishell: syntax error: unclosed quote\n");
        ft_malloc(0, 0);
        exit(1);
    }
    while (token->token[i])
    {
        if (token->token[i] != '\'' && token->token[i] != '\"')
            len++;
        i++;
    }
    new = ft_malloc(len + 1, 1);
    i = 0;
    len = 0;
    while (token->token[i])
    {
        if (token->token[i] != '\'' && token->token[i] != '\"')
        {
            new[len] = token->token[i];
            len++;
        }
        i++;
    }
    new[len] = '\0';
    token->token = new;
}