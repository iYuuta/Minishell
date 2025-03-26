#include "libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	size_t	i;
	size_t	size;
	char	*str;

	if (!s2)
		return (s1);
	if (s1[0] == '\0' && s2[0] == '\0')
		return (ft_strdup("\0"));
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	i = 0;
	str = (char *)ft_malloc((size + 1) * sizeof(char), 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = ' ';
	while (i < size)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}
