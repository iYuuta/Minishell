#include "../minishell.h"

const char *token_type_to_string(t_token_type type)
{
    switch (type)
    {
        case WORD: return "WORD";
        case HEREDOCTEXT: return "HEREDOCTEXT";
        case file: return "file";
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
        case VAR_ASSING: return "VAR_ASSING";
        case BACKGROUND: return "BACKGROUND";
        default: return "UNKNOWN";
    }
}

t_arg *parse_args(char *str, t_env *env)
{
    t_arg *head = NULL;
    char **args;
    int size;
    
    size = 0;
    str = expand_vars(str, env);
    args = split_args(str, &size);
    if (!args)
    {
        printf("bash: syntax error unclosed quotes\n");
        ft_malloc(0, 0);
        return (NULL);
    }
    head = tokenize_arg(args, env);
    // if (!check_uncompleted_cmd(head))
    // {
    //     ft_malloc(0, 0);
    //     return (NULL);
    // }
    // while (head)
    // {
    //     printf("token-> %s    type-> %s\n", head->token, token_type_to_string(head->type));
    //     head = head->next;
    // }
    return (head);   
}

