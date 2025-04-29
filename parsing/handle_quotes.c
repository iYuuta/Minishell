#include "../minishell.h"

int	get_index(char *str, char c)
{
	int	i;

	i = 1;
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
	*j = 0;
	while (str[*j] && !ft_strchr(" <>|&", str[*j])
		&& (str[*j] < 9 || str[*j] > 13))
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

t_arg	*split_args(char *str, t_env *env)
{
	int		i;
	int		j;
	t_arg	*head;
	t_arg	*tmp;

	i = 0;
	head = NULL;
	while (str[i])
	{
		j = 0;
		while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
			i++;
		if (!str[i])
			break ;
		if (ft_strchr("<>|&", str[i]))
			tmp = ft_lstnew(handle_operators(str + i, &j));
		else
			tmp = ft_lstnew(handle_normal_word(str + i, &j));
		tmp->env = env;
		i += j;
		ft_lstadd_back(&head, tmp);
	}
	return (head);
}
