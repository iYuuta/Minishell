#include "../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (len > slen - start)
		len = slen - start;
	str = (char *)ft_malloc((len + 1) * sizeof(char), 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
