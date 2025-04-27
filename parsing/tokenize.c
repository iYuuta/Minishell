#include "../minishell.h"

int is_flag(char *str)
{
    if (!str && !(*str))
        return (0);
    if (*str == '\'' || *str == '\"')
        str++;
    if (*str++ == '-' && *str)
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
    token = token->next;
    if (token)
        token->type = file;
    return (token);
}

static void print_error(char *str, int flag)
{
    if (flag)
    {
        return_value(2, 1);
        ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
        ft_putstr_fd(str, 2);
    }
    else
    {
        return_value(126, 1);
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(str, 2);
        ft_putendl_fd(": Is a directory", 2);
        return ;
    }
    write(2, "\n", 2);
}

int check_first_arg(char *str)
{
    struct stat info;

    if (!ft_strcmp(str, "|"))
        return (print_error(str, 1), 1);
    if (stat(str, &info) == -1)
        return (0);
    if (ft_strchr(str, '/') && S_ISDIR(info.st_mode))
        return (print_error(str, 0), 1);
    return (0);
}

int identify_tokens(t_arg *token)
{
    if (token && check_first_arg(token->token))
        return (1);
    while (token)
    {
        if (!ft_strcmp(token->token, "||") || !ft_strcmp(token->token, "&&"))
            return (print_error(token->token, 1), 1);
        if (is_redirection(token->token))
        {
            token->type = is_redirection(token->token);
            if (!token->next)
                return (print_error("new line", 1), 1);
            if (is_redirection(token->next->token))
                return (print_error(token->next->token, 1), 1);
            token = handle_redir(token);
            if (!token)
                break;
        }
        else
            token->type = is_pipe(token->token);
        if (token->type == PIPE && (!token->next || !ft_strcmp(token->next->token, "|")))
            return (print_error(token->token, 1), 1);
        token = token->next;
    }
    return (0);
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
    if (identify_tokens(head))
        return (NULL);
    return (head);
}
