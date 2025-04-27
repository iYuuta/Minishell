#include "libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*str;

	if (!s2)
		return (ft_strdup(s1));
	if (s1[0] == '\0' && s2[0] == '\0')
		return (ft_strdup(""));
	size = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)ft_malloc((size + 1) * sizeof(char), 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
