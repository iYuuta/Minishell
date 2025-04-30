#include "../minishell.h"

int	skip_chars_heredoc(char *str)
{
	int	i;

	i = 1;
	while (str && !ft_strchr(" \'\"$", str[i]))
		i++;
	return (i);
}

char	*get_var_heredoc(t_env *env, char *str)
{
	if (str && !str[0])
		return (ft_strdup(""));
	while (env)
	{
		if (!ft_strcmp(env->name, str))
			return (ft_strdup(env->arg));
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*expand_heredoc(t_env *env, char *str)
{
	char	*strings[4];
	int		i;
	int		j;

	i = -1;
	while (str[++i])
	{
		if (str[i] && str[i] == '$')
		{
			j = -1;
			strings[3] = ft_strdup("");
			strings[0] = ft_substr(str, 0, i);
			strings[1] = ft_substr(str, i, skip_chars_heredoc(str + i));
			strings[2] = ft_substr(str, i + skip_chars_heredoc(str + i),
					ft_strlen(str + (i + skip_chars_heredoc(str + i))));
			strings[1] = get_var_heredoc(env, strings[1] + 1);
			while (++j < 3)
				strings[3] = ft_strjoin(strings[3], strings[j]);
			str = strings[3];
		}
		if (!str[i])
			break ;
	}
	return (str);
}
