#include "../minishell.h"

int is_flag(char *str)
{
    if (!str && !(*str))
        return (0);
    if (*str == '\'' || *str == '\"')
        str++;
    if (*str == '-')
        return (1);
    return (0);
}

int is_redirection(char *str)
{
    if (!strcmp(str, "<<"))
        return (HEREDOC);
    if (!strcmp(str, ">>"))
        return (REDIR_APPEND);
    if (!strcmp(str, "<"))
        return (REDIR_IN);
    if (!strcmp(str, ">"))
        return (REDIR_OUT);
    return (0);
}

int is_operator(char *str)
{
    if (!strcmp(str, "|"))
        return (PIPE);
    if (*str == '$')
        return (VARIABLE);
    return (WORD);
}

t_arg *handle_redir(t_arg *token)
{
    if (token->type == HEREDOC && token->next)
        token->next = read_here_doc(token->next);
    // if (token->next && ft_strchr("<>"))
    token = token->next;
    if (token && token->prev->type != HEREDOC && token)
        token->type = file;
    return (token);
}

int variable_assign(t_arg *token)
{
    char *assing;

    assing = ft_strchr(token->token, '=');
    if (!assing || assing == token->token)
        return (0);
    if (ft_strchr("\'\" ", *(assing - 1)) || ft_strchr(" ", *(assing + 1)))
        return (0);
    return (1);
}
void identify_tokens(t_arg *token)
{
    int i;

    i = 0;
    while (token)
    {
        if (i == 0 && variable_assign(token))
            token->type = VAR_ASSING;
        else if (i == 0 && !ft_strchr("<>|&$", token->token[0]))
            token->type = CMD;
        else if (is_flag(token->token))
            token->type = FLAG;
        else if (is_redirection(token->token))
        {
            token->type = is_redirection(token->token);
            token = handle_redir(token);
            if (!token)
                break;
            if (token->next && !ft_strchr("<>", token->next->token[0]))
            {
                token = token->next;
                if (variable_assign(token))
                    token->type = VAR_ASSING;
                else
                    token->type = CMD;
            }
        }
        else
            token->type = is_operator(token->token);
        if (token->type == PIPE)
        {
            if (token->next && !ft_strchr("<>", token->next->token[0]))
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
    tmp = head;
    while (tmp)
    {
        if (tmp->type == VAR_ASSING)
            head->env = env_innit(tmp);
        tmp = tmp->next;
    }
    // expand_vars(head);
    // polish_tokens(head);
    return (head);
}
