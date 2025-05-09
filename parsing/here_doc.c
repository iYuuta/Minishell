#include "../minishell.h"

static int	get_new_stop_len(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			len++;
		i++;
	}
	return (len);
}

static void	fill_new_stop(char *new, char *str)
{
	int		i;
	int		len;
	char	c;

	i = 0;
	len = 0;
	while (str[i])
	{
		c = str[i];
		if (c == '\'' || c == '\"')
		{
			while (str[++i] && str[i] != c)
				new[len++] = str[i];
			if (!str[i])
				break ;
		}
		else
			new[len++] = str[i];
		i++;
	}
	new[len] = '\0';
}

char	*new_stop(char *str)
{
	char	*new;
	int		len;

	len = get_new_stop_len(str);
	new = ft_malloc(len + 1, 1);
	if (!new)
		return (NULL);
	fill_new_stop(new, str);
	return (new);
}

void	update_heredoc_attr(char **stop, int *flag, char **str, char *token)
{
	*flag = 1;
	if (ft_strchr(token, '\'') || ft_strchr(token, '\"'))
		*flag = 0;
	*stop = polish(token);
	*str = ft_strdup("");
	if (g_ctrl != 2)
		g_ctrl = 3;
}

char	*read_here_doc(char *token, t_env *env, int pipe[2])
{
	char	*stop;
	char	*str;
	char	*tmp[2];
	int		flag;

	update_heredoc_attr(&stop, &flag, &str, token);
	while (1 && g_ctrl != 2)
	{
		tmp[0] = readline("> ");
		if (!tmp[0])
			return (token = str, token);
		if (g_ctrl == 2)
			return (free(tmp[0]), close(pipe[0]), close(pipe[1]), NULL);
		if (!ft_strcmp(tmp[0], stop))
			return (token = str, free(tmp[0]), token);
		if (flag)
			tmp[1] = expand_heredoc(env, tmp[0]);
		else
			tmp[1] = tmp[0];
		str = ft_strjoin(str, tmp[1]);
		str = ft_strjoin(str, "\n");
		free (tmp[0]);
	}
	return (NULL);
}
