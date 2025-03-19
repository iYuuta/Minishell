#include "../minishell.h"

//this is a grabage collector when ever u call 
//ft_malloc it does the same as regular malloc but it saves the allocate
//pointer so we can free it later on

void *ft_malloc(size_t size, int flag)
{
    static void **collector;
    static int i;

    if (!collector)
    {
        collector = malloc(sizeof(void *) * 1000);
        while (i < 1000)
            collector[i++] = NULL;
        i = 0;
    }
    if (flag)
    {
        collector[i++] = malloc(size);
        return (collector[i - 1]);
    }
    i = 0;
    if (!flag)
    {
        while (i < 1000)
        {
            if (collector[i] == NULL)
                break;
            free(collector[i]);
            i++;
        }
        free(collector);
        collector = NULL;
    }
    i = 0;
    return (NULL);
}
