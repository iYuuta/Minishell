#include "../minishell.h"

char	*ft_env_join(char *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*str;

	if (!s1)
		return (ft_env_strdup(s2));
	if (!s2)
		return (ft_env_strdup(s1));
	if (s1[0] == '\0' && s2[0] == '\0')
		return (ft_env_strdup(""));
	size = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)env_malloc((size + 1) * sizeof(char), 1);
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

char	*ft_env_strdup(const char *s1)
{
	size_t	len;
	char	*dup;

	len = (ft_strlen(s1) + 1);
	dup = (char *)env_malloc(len * sizeof(char), 1);
	ft_strlcpy(dup, s1, len);
	return (dup);
}

char	*ft_env_sub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (slen <= start)
		return (NULL);
	if (len > slen - start)
		len = slen - start;
	str = (char *)env_malloc((len + 1) * sizeof(char), 1);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
