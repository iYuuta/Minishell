#include "../minishell.h"

int	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (get_index(str + i, str[i]) == -1)
				return (1);
			i += get_index(str + i, str[i]);
		}
		i++;
	}
	return (0);
}

t_cmd	*parse_args(char *str, t_env *env)
{
	t_arg	*head;
	t_cmd	*cmd;
	int		size;

	size = 0;
	if (check_quotes(str))
	{
		ft_putstr_fd("minishell: syntax error unclosed quotes\n", 2);
		ft_malloc(0, 0);
		return (NULL);
	}
	str = expand_vars(env, str, 1);
	if (str && !str[0])
		return (return_value(0, 1), NULL);
	head = split_args(str, env);
	if (identify_tokens(head))
		return (NULL);
	cmd = finish_parse(head, env);
	return (cmd);
}
