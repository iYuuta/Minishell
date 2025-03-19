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
    if (!strcmp(str, "|"))
        return (PIPE);
    if (!strcmp(str, "<"))
        return (REDIR_IN);
    if (!strcmp(str, ">"))
        return (REDIR_OUT);
    if (!strcmp(str, "<<"))
        return (HEREDOC);
    if (!strcmp(str, ">>"))
        return (REDIR_APPEND);
    if (*str == '$')
        return (VARIABLE);
    return (WORD);
}
