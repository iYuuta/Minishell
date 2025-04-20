#include "../minishell.h"

const char *token_type_to_string(t_token_type type)
{
    switch (type)
    {
        case WORD: return "WORD";
        case file: return "file";
        case CMD: return "CMD";
        case FLAG: return "FLAG";
        case PIPE: return "PIPE";
        case REDIR_OUT: return "REDIR_OUT";
        case REDIR_APPEND: return "REDIR_APPEND";
        case REDIR_IN: return "REDIR_IN";
        case HEREDOC: return "HEREDOC";
        default: return "UNKNOWN";
    }
}

t_cmd *parse_args(char *str, t_env *env)
{
    t_arg *head = NULL;
    t_cmd *cmd;
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
    // while (head)
    // {
    //     printf("token-> %s    type-> %s\n", head->token, token_type_to_string(head->type));
    //     head = head->next;
    // }
    cmd = finish_parse(head, env);
    // while (cmd)
    // {
    //     while (cmd->tokens)
    //     {
    //         printf("token-> %s    type-> %s\n", cmd->tokens->token, token_type_to_string(cmd->tokens->type));
    //         cmd->tokens = cmd->tokens->next;
    //     }
    //     while (cmd->file)
    //     {
    //         printf("file name-> %s    type-> %s\n", cmd->file->file, token_type_to_string(cmd->file->type));
    //         cmd->file = cmd->file->next;
    //     }
    //     cmd = cmd->next;
    // }
    return (cmd);
}

