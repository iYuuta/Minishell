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
		if (str[i] && ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13)))
		{
			while (str[i] && ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13)))
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
	if (str[i] && !str[i])
		return (1);
	if (str[i] && str[i] == '?')
		return (2);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
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

int    get_skip_index(char *str, int i)
{
    int yuta;

    if (ft_strchr("><", str[i]))
        return (skip_redirections(str + i));
    else if (str[i] && str[i] == '\'')
    {
        while (str[i] && str[i] == '\'' && str[i + 1])
        {
            yuta = get_index(str + i, '\'');
            if (yuta < 0)
                return (i);
            i += yuta;
        }
    }
    return (i);
}

char	*expand_vars(t_env *env, char *str, int exp)
{
	int	i;
	int	flag;

	i = -1;
	flag = 2;
	while (i < (int)ft_strlen(str) && str[++i])
	{
		if (str[i] && flag % 2 == 0 && ft_strchr("><\'", str[i]))
			i += get_skip_index(str, i);
		else if (str[i] && exp && flag % 2 == 0 && str[i] == '=')
			i += skip_assigning(str + i);
		else if (str[i] && str[i] == '\"')
			flag++;
		else if (str[i] && str[i] == '$' && str[i + 1]
			&& !ft_strchr("%%$^=+./\"\' ", str[i + 1]))
		{
			str = expand_str(str, env, &i, skip_chars(str + i));
			if (i == -1 || !str[i])
				break ;
			if (i == 0)
				i--;
		}
	}
	return (str);
}
