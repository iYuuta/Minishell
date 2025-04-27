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

int check_quotes(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\"' || str[i] == '\'')
        {
            if (get_index(str + i, str[i]) == -1)
                return (1);
            i += get_index(str + i, str[i]);
        }
        i++;
    }
    return (0);
}

t_cmd *parse_args(char *str, t_env *env)
{
    t_arg *head = NULL;
    t_cmd *cmd;
    char **args;
    int size;

    size = 0;
    if (check_quotes(str))
    {
        ft_putstr_fd("minishell: syntax error unclosed quotes\n", 2);
        ft_malloc(0, 0);
        return (NULL);
    }
    str = expand_vars(env, str, 1);
    args = split_args(str, &size);
    head = tokenize_arg(args, env);
    if (!head)
        return (NULL);
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

