#include "../minishell.h"

void polish(t_arg *token)
{
    char *new;
    char c;
    int i;
    int len;

    i = 0;
    len = 0;
    while (token->token[i])
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

int check_uncompleted_cmd(t_arg *token)
{
    t_arg *tmp;

    if (token->type == PIPE)
    {
        printf("bash: syntax error near unexpected token `|'\n");
        return (0);
    }
    tmp = ft_lstlast(token);
    if (tmp->type == PIPE || (tmp->type >= REDIR_OUT && tmp->type <= HEREDOC))
    {
        printf("bash: syntax error near unexpected token `new line'\n");
        return (0);
    }
    while (token)
    {
        if (token->next && (is_redirection(token->token) || token->type == PIPE) && (is_redirection(token->next->token) || token->next->type == PIPE))
            return (printf("bash: syntax error near unexpected token `%s'\n", token->token), 0);
        token = token->next;
    }
    return (1);
}