#include "../minishell.h"

int check_uncompleted_cmd(t_arg *token)
{
    t_arg *tmp;

    if (token->type == PIPE)
    {
        printf("bash: syntax error near unexpected token `|'\n");
        return (1);
    }
    tmp = ft_lstlast(token);
    if (tmp->type == PIPE || (tmp->type >= REDIR_OUT && tmp->type <= HEREDOC))
    {
        printf("bash: syntax error near unexpected token `new line'\n");
        return (1);
    }
    while (token)
    {
        if (token->next && (is_redirection(token->token) || token->type == PIPE) && (is_redirection(token->next->token) || token->next->type == PIPE))
            return (printf("bash: syntax error near unexpected token `%s'\n", token->token), 0);
        token = token->next;
    }
    return (0);
}
