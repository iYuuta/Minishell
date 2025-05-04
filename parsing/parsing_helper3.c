#include "../minishell.h"

char	*safe_expand(char *str)
{
	char	**args;
	char	*tmp;
	int		i;

	tmp = ft_strdup("");
	i = 0;
	args = ft_split(str, ' ');
	while (args[i])
	{
		args[i] = ft_strjoin("\"", args[i]);
		args[i] = ft_strjoin(args[i], "\"");
		i++;
	}
	i = 0;
	while (args[i])
	{
		tmp = ft_strjoin(tmp, args[i]);
		if (args[i + 1])
			tmp = ft_strjoin(tmp, " ");
		i++;
	}
	return (tmp);
}

char	*safe_trim(char *str)
{
	char	*start;
	char	*end;
	char	*new;
	size_t	len;

	start = ft_strchr(str, '\"');
	end = ft_strrchr(str, '\"');
	if (!start || !end || start == end)
		return (str);
	len = end - start - 1;
	new = ft_malloc(len + 1, 1);
	ft_strlcpy(new, start + 1, len + 1);
	return (new);
}

int	is_flag(char *str)
{
	if (!str && !(*str))
		return (0);
	if (*str == '\'' || *str == '\"')
		str++;
	if (*str++ == '-' && *str)
		return (1);
	return (0);
}

int	is_redirection(char *str)
{
	if (!ft_strcmp(str, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(str, ">>"))
		return (REDIR_APPEND);
	if (!ft_strcmp(str, "<"))
		return (REDIR_IN);
	if (!ft_strcmp(str, ">"))
		return (REDIR_OUT);
	return (0);
}

int	is_pipe(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (PIPE);
	return (WORD);
}
