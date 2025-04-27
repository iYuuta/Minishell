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

int	get_skip_index(char *str, int i)
{
	if (ft_strchr("><", str[i]))
		return (skip_redirections(str + i));
	else if (str[i] && str[i] == '\'')
		return (get_index(str + i, '\''));
	return (0);
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
			i += get_skip_index(str, i);
		else if (exp && flag % 2 == 0 && str[i] == '=')
			i += skip_assigning(str + i);
		else if (str[i] && str[i] == '\"')
			flag++;
		else if (str[i] == '$' && str[i + 1]
			&& !ft_strchr("%%$^=+./\"\' ", str[i + 1]))
		{
			skip = skip_chars(str + i);
			str = expand_str(str, env, &i, skip);
		}
		if (i == -1 || !str[i])
			break ;
	}
	return (str);
}
