#include "../minishell.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dup;

	len = (ft_strlen(s1) + 1);
	dup = (char *)ft_malloc(len * sizeof(char), 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s1, len);
	return (dup);
}
