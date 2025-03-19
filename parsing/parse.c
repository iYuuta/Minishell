#include "../minishell.h"

void identify_tokens(t_arg *token)
{
    int i;
    int size;

    i = 0;
    size = ft_lstsize(token);
    while (i < size)
    {
        if (i == 0)
            token->type = CMD;
        else if (is_flag(token->token))
            token->type = FLAG;
        else
                token->type = is_operator(token->token);
        if (token->type == PIPE)
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

t_arg *tokenize_arg(int ac, char **av)
{
    int i;
    char *str;
    t_arg *head;
    t_arg *tmp;

    i = -1;
    head = NULL;
    while (++i < ac)
    {
        str = av[i];tmp = ft_lstnew(str);
        ft_lstadd_back(&head, tmp);
    }
    identify_tokens(head);
    polish_tokens(head);
    return (head);
}

const char *token_type_to_string(t_token_type type)
{
    switch (type)
    {
        case WORD: return "WORD";
        case CMD: return "CMD";
        case FLAG: return "FLAG";
        case PIPE: return "PIPE";
        case REDIR_OUT: return "REDIR_OUT";
        case REDIR_APPEND: return "REDIR_APPEND";
        case REDIR_IN: return "REDIR_IN";
        case HEREDOC: return "HEREDOC";
        case DQUOTE_STRING: return "DQUOTE_STRING";
        case SQUOTE_STRING: return "SQUOTE_STRING";
        case VARIABLE: return "VARIABLE";
        case LOGICAL_AND: return "LOGICAL_AND";
        case LOGICAL_OR: return "LOGICAL_OR";
        case BACKGROUND: return "BACKGROUND";
        default: return "UNKNOWN";
    }
}

int get_quote(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        while (str[i] && str[i] != '"' && str[i] != '\'')
            i++;
        if (str[i] && (str[++i] == ' ' || str[i] == '\''))
            return (i);
        else if (str[i] == '\'' || str[i] == '\"')
        {
            while (str[i] && (str[i] == '"' || str[i] == '\''))
                i++;
        }
        else
        {
            while (str[i] != ' ')
                i++;
            return (i);
        }
    }
    return (i);
}

int get_single_quote(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        while (str[i] && str[i] != '\'')
            i++;
        if (str[i] && str[++i] != '\'')
            return (i);
        else
        {
            while (str[i] && str[i] == '\'')
                i++;
        }
    }
    return (i);
}

char **split_args(char *str, int *size)
{
    int i;
    int j;
    char **args;
    char *arg;

    i = 0;
    j = 0;
    args = (char **)ft_malloc(sizeof(char *) * 100, 1);
    while (str[i])
    {
        while (str[i] == ' ')
            i++;
        if (str[i] == '"' || str[i] == '\'')
        {
            j = get_quote(str + i + 1);
            printf("%d\n", j);
            arg = ft_substr(str, i, j + 1);
            i += j + 1;
            j = 1;
        }
        else
        {
            while (str[i + j] && str[i + j] != ' ')
                j++;
            arg = ft_substr(str, i, j);
            i += j;
            j = 1;
        }
        printf("|%s|\n", arg);
        args[*size] = arg;
        *size += 1;
    }
    // args[*size] = NULL;
    return (args);
}

t_arg *parse_args(char *str)
{
    t_arg *head = NULL;
    char **args;
    int size;
    
    size = 0;
    args = split_args(str, &size);
    head = tokenize_arg(size, args);
    while (head)
    {
        printf("token->%s    type->%s\n", head->token, token_type_to_string(head->type));
        head = head->next;
    }
    return (head);
}
