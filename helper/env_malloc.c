#include "../minishell.h"

void *env_malloc(size_t size, int flag)
{
    static void **collector;
    static int i;

    if (!collector)
    {
        collector = malloc(sizeof(void *) * 1000);
        if (!collector)
            return (NULL);
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