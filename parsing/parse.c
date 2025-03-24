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
        case DQUOTE_STRING: return "DQUOTE_STRING";
        case SQUOTE_STRING: return "SQUOTE_STRING";
        case VARIABLE: return "VARIABLE";
        case LOGICAL_AND: return "LOGICAL_AND";
        case LOGICAL_OR: return "LOGICAL_OR";
        case BACKGROUND: return "BACKGROUND";
        default: return "UNKNOWN";
    }
}

t_arg *parse_args(char *str)
{
    t_arg *head = NULL;
    char **args;
    int size;
    
    size = 0;
    args = split_args(str, &size);
    head = tokenize_arg(args);
    while (head)
    {
        printf("token-> %s    type-> %s\n", head->token, token_type_to_string(head->type));
        head = head->next;
    }
    return (head);   
}

// #include "../minishell.h"

// int get_index(char *str, char c, char d)
// {
//     int i;
//     int nested_index;

//     i = 1;
//     while (str[i])
//     {
//         if (str[i] == d)
//         {
//             nested_index = get_index(str + i, d, c);
//             if (nested_index == -1)
//                 return -1;
//             i += nested_index;
//         }
//         if (str[i] == c)
//             return (i);
//         i++;
//     }
//     return -1; // Return -1 if character `c` is not found
// }

// int ft_get_quote(char *str, char c)
// {
//     int i;
//     int j;
//     char tmp;

//     i = 0;
//     j = 0;
//     tmp = '\''; 
//     if (c == '\'')
//         tmp = '"';
//     j = get_index(str, c, tmp);
//     if (!str[++j] || (ft_strchr(" <>|&$", str[j])))
//         return (j);
//     return (j);
// }

// // int get_quote(char *str, char c)
// // {
// //     int i;
// //     char tmp;

// //     tmp = '\'';
// //     if (c == '\'')
// //         tmp = '\"';
// //     i = 0;
// //     while (str[i])
// //     {
// //         while (str[i] && str[i] == ' ')
// //             i++;
// //         if (str[i] == c)
// //         {
// //             i = ft_get_quote(str + i, tmp);
// //         }
// //         if (str[i] && (str[++i] == ' ' || !ft_isalnum(str[i])) || ft_strchr("<>|&$", str[i]))
// //             return (i);
// //         else if (ft_isalnum(str[i]))
// //         {
// //             while (str[i] && ft_isalnum(str[i]))
// //                 i++;
// //         }
// //     }
// //     return (i);
// // }

// char **split_args(char *str, int *size)
// {
//     int i;
//     int j;
//     char **args;
//     char *arg;

//     i = 0;
//     j = 0;
//     args = (char **)ft_malloc(sizeof(char *) * 100, 1);
//     while (str[i])
//     {
//         j = 0;
//         while (str[i] == ' ')
//             i++;
//         while (str[i + j] && !ft_strchr(" <>|&$", str[i + j]))
//         {
//             if (str[i + j] == '\'' || str[i] == '\"')
//                 j = ft_get_quote(str, str[i]);
//             else
//                 j++;
//         }
//         arg = ft_substr(str, i, j);
//         i += j;
//         printf("|%s|\n", arg);
//         args[*size] = arg;
//         *size += 1;
//         while (str[i] == ' ')
//             i++;
//     }
//     args[*size] = NULL;
//     return (args);
// }
