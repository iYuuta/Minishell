#include "../minishell.h"

int polished_strlen(char *token)
{
    int len;
    int i;
    char c;

    i = 0;
    len = 0;
    c = 0;
    while (token[i])
    {
        if (c != 0 && token[i] == c)
        {
            len--;
            c = 0;
        }
        else if (c == 0 && token[i] == '\'' || token[i] == '\"')
        {
            len--;
            c = token[i];
        }
        len++;
        i++;
    }
    return (len);
}

char *polish(char *token)
{
    int len;
    int i;
    char quote;
    char *new_token;

    len = polished_strlen(token);
    new_token = ft_malloc(len + 1, 1);
    new_token[len] = '\0';
    i = 0;
    quote = 0;
    while (i < len)
    {
        if (quote == 0 && (*token == '\'' || *token == '\"'))
           quote = *token;
        else if (quote != 0 && quote == *token)
           quote = 0;
        else
            new_token[i++] = *token;
        token++;
    }
    return (new_token);
}
