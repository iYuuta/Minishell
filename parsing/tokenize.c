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
    if (!ft_strcmp(str, "<<"))
        return (HEREDOC);
    if (!ft_strcmp(str, ">>"))
        return (REDIR_APPEND);
    if (!ft_strcmp(str, "<"))
        return (REDIR_IN);
    if (!ft_strcmp(str, ">"))
        return (REDIR_OUT);
    return (0);
}

int is_pipe(char *str)
{
    if (!ft_strcmp(str, "|"))
        return (PIPE);
    return (WORD);
}

t_arg *handle_redir(t_arg *token)
{
    if (token->type == HEREDOC && token->next)
        token->next = read_here_doc(token->next);
    token = token->next;
    if (token && token->prev->type != HEREDOC && token)
        token->type = file;
    return (token);
}

void identify_tokens(t_arg *token)
{
    int i;

    i = 0;
    while (token)
    {
        if (i == 0 && !ft_strchr("<>", token->token[0]))
            token->type = CMD;
        else if (is_flag(token->token))
            token->type = FLAG;
        else if (is_redirection(token->token))
        {
            token->type = is_redirection(token->token);
            token = handle_redir(token);
            if (!token)
                break;
        }
        else
            token->type = is_pipe(token->token);
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

t_arg *tokenize_arg(char **av, t_env *env)
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
        tmp->env = env;
        ft_lstadd_back(&head, tmp);
    }
    identify_tokens(head);
    // expand_vars(head);
    polish_tokens(head);
    return (head);
}
