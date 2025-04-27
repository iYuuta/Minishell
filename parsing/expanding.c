#include "../minishell.h"

int	skip_redirections(char *str)
{
	int	i;

	i = 0;
	if (str[i] && ft_strchr("><", str[i]))
	{
		i++;
		if (str[i] && ft_strchr("><", str[i]))
			i++;
		if (str[i] && str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		{
			while (str[i] && str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
				i++;
		}
		while (str[i] && str[i] != ' ' && (str[i] < 9 || str[i] > 13))
			i++;
	}
	return (i);
}

int	skip_chars(char *str)
{
	int	i;

	i = 1;
	if (str[i] && str[i] == '?')
		return (2);
	while (str && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*selective_expanding(char *str, t_env *env)
{
	t_env	*variable;

    variable = get_env(env, str + 1);
    if (!ft_strcmp(str + 1, "PATH") && !variable)
        variable = env;
    if (!variable)
        str = ft_strdup("\0");
    else
        str = variable->arg;
    return (str);
}

char	*expand_str(char *str, t_env *env, int *i, int skip)
{
	char	*strings[4];
	int		j;

    j = -1;
    strings[3] = ft_strdup("");
    strings[0] = ft_substr(str, 0, *i);
    strings[1] = ft_substr(str, *i, skip);
    strings[2] = ft_substr(str, *i + skip, ft_strlen(str + (*i + skip)));
    if (str[*i + 1] && str[*i + 1] == '?')
        strings[1] = ft_itoa(return_value(0, 0));
    else
        strings[1] = selective_expanding(strings[1], env);
    while (++j < 3)
        strings[3] = ft_strjoin(strings[3], strings[j]);
    *i = ft_strlen(strings[0]) + ft_strlen(strings[1]) - 1;
    if (*i < 0)
        *i = 0;
    return (strings[3]);
}

int	skip_assigning(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (ft_strchr("\'\"", str[i]))
			i += get_index(str + i, str[i]);
		if (!str[i])
			break ;
		if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			return (i);
		i++;
	}
	return (i);
}

char	*expand_vars(t_env *env, char *str, int exp)
{
	int	i;
	int	flag;
	int	skip;

	i = -1;
	flag = 2;
	while (str[++i])
	{
		if (flag % 2 == 0 && ft_strchr("><", str[i]))
			i += skip_redirections(str + i);
		else if (exp && flag % 2 == 0 && str[i] == '=')
			i += skip_assigning(str + i);
		else if (flag % 2 == 0 && str[i] && str[i] == '\'')
			i += get_index(str + i, '\'');
		else if (str[i] && str[i] == '\"')
			flag++;
		else if (str[i] && str[i] == '$' && str[i + 1] && !ft_strchr("%%$^=+./\"\' ", str[i + 1]))
		{
			skip = skip_chars(str + i);
			str = expand_str(str, env, &i, skip);
		}
		if (i == -1 || !str[i])
			break ;
	}
	return (str);
}
