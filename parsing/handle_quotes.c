#include "../minishell.h"

int	get_index(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*handle_operators(char *str, int *j)
{
	*j = 1;
	if (ft_strchr("<>|&", str[0]) && str[1] && str[0] == str[1])
		*j = 2;
	return (ft_substr(str, 0, *j));
}

char	*handle_normal_word(char *str, int *j)
{
	char *word;

	*j = 0;
	while (str[*j] && !ft_strchr(" <>|&", str[*j]) && (str[*j] < 9 || str[*j] > 13))
	{
		if (ft_strchr("\'\"", str[*j]) && get_index(str + *j, str[*j]) == -1)
			return (NULL);
		if (ft_strchr("\'\"", str[*j]))
			*j += get_index(str + *j, str[*j]) + 1;
		else
			(*j)++;
	}
	return (ft_substr(str, 0, *j));
}

char	**split_args(char *str, int *size)
{
	int		i;
	int		j;
	char	**args;

	i = 0;
	*size = 0;
	args = (char **)ft_malloc(sizeof(char *) * 100, 1);
	while (str[i])
	{
		j = 0;
		while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
			i++;
		if (!str[i])
			break ;
		if (ft_strchr("<>|&", str[i]))
			args[*size] = handle_operators(str + i, &j);
		else
			args[*size] = handle_normal_word(str + i, &j);
		if (!args[*size])
			return (NULL);
		i += j;
		(*size)++;
	}
	args[*size] = NULL;
	return (args);
}
