#include "../minishell.h"

char *wild_card(char *str)
{
    char path[] = ".";
    struct dirent *entry;
    DIR *dir;
    
    dir = opendir(path);
    entry = readdir(dir);
    while (entry)
    {
        printf("dir name-> %s\n", entry->d_name);
        entry = readdir(dir);
    }
}