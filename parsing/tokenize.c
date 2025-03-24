#include "../minishell.h"

int is_flag(char *str)
{
    if (!str)
        return (0);
    if (str[0] == '\'' || str[0] == '\"')
        str++;
    if (*str == '-' && str[1])
        return (1);
    return (0);
}

int is_operator(char *str)
{
    if (!strcmp(str, "||"))
        return (LOGICAL_OR);
    if (!strcmp(str, "&&"))
        return (LOGICAL_AND);
    if (!strcmp(str, "&"))
        return (PIPE);
    if (!strcmp(str, "|"))
        return (PIPE);
    if (!strcmp(str, "<<"))
        return (HEREDOC);
    if (!strcmp(str, ">>"))
        return (REDIR_APPEND);
    if (!strcmp(str, "<"))
        return (REDIR_IN);
    if (!strcmp(str, ">"))
        return (REDIR_OUT);
    if (*str == '$')
        return (VARIABLE);
    return (WORD);
}

void identify_tokens(t_arg *token)
{
    int i;
    int size;

    i = 0;
    size = ft_lstsize(token);
    while (i < size)
    {
        if (i == 0 && !ft_strchr("<>|&$", token->token[0]))
            token->type = CMD;
        else if (is_flag(token->token))
            token->type = FLAG;
        else
            token->type = is_operator(token->token);
        if (token->type == REDIR_IN || token->type == REDIR_OUT || token->type == REDIR_APPEND)
        {
            if (token->next)
            {
                token = token->next;
                i++;
                token->type = file;
            }
        }
        if (token->type == PIPE || token->type == LOGICAL_OR || token->type == LOGICAL_AND)
        {
            if (token->next)
            {
                token = token->next;
                i++;
                token->type = CMD;
            }
        }
        i++;
        token = token->next;
    }
}

void polish_tokens(t_arg *tokens)
{
    t_arg *tmp;

    tmp = tokens;
    while (tmp)
    {
        if (tmp->type == CMD || tmp->type == FLAG)
            polish(tmp);
        tmp = tmp->next;
    }
}

t_arg *tokenize_arg(char **av)
{
    int i;
    char *str;
    t_arg *head;
    t_arg *tmp;

    i = -1;
    head = NULL;
    while (av[++i])
    {
        tmp = ft_lstnew(av[i]);
        ft_lstadd_back(&head, tmp);
    }
    identify_tokens(head);
    polish_tokens(head);
    return (head);
}
