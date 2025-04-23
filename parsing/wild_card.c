#include "../minishell.h"

// char *get_pattern(char *str, int *j)
// {
//     int i;
//     char *pattern;

//     i = 0;
//     while (str[i] && str[i] == '*')
//         i++;
//     while (str[i])
//     {
//         if (str[i] == '*')
//             break ;
//         i++;
//     }
//     *j += i;
//     pattern = ft_substr(str, 1, i);
//     printf("%s\n", pattern);
//     return (pattern);
// }

// int is_match(char *name, char *wildcard)
// {
//     int i;
//     int j;
//     char *pattern;

//     i = 0;
//     j = 0;
//     if (wildcard[i] && wildcard[i] == '*' && wildcard[i + 1] == '\0')
//         return (1);
//     while (name[i])
//     {
//         pattern = get_pattern(wildcard + j, &j);
//         if (ft_strnstr(name + i, pattern, ft_strlen(name + i)))
//             i += ft_strlen(pattern);
//         if (name[i] == '\0' && )
//             return (1);
//         i++;
//     }
// }

// char *get_dir(char *str)
// {
//     struct dirent *entry;
//     DIR *dir;
//     t_arg *head;
//     t_arg *tmp;
    
//     head = NULL;
//     dir = opendir(".");
//     tmp = ft_malloc(sizeof(t_arg), 1);
//     entry = readdir(dir);
//     {
//         if (is_match(entry->d_name, str))
//         {
//             tmp->token = ft_strdup(entry->d_name);
//             tmp->type = WORD;
//             ft_lstadd_back(&head, tmp);
//             tmp = ft_malloc(sizeof(t_arg), 1);
//         }
//         entry = readdir(dir);
//     }
// }

// t_arg *wild_card(t_arg *token)
// {
//     struct dirent *entry;
//     DIR *dir;
    
//     if ()
// }
