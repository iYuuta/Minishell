#include "../minishell.h"

t_arg	*copy_token(t_arg *token)
{
	t_arg	*copy;

	copy = ft_malloc(sizeof(t_arg), 1);
	copy->head = NULL;
	copy->token = token->token;
	copy->type = token->type;
	copy->env = token->env;
	copy->next = NULL;
	copy->prev = NULL;
	return (copy);
}

t_cmd	*last_cmd(t_cmd *lst)
{
	t_cmd	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	temp = last_cmd(*lst);
	temp->next = new;
}

char	*selective_expanding(char *str, t_env *env)
{
	t_env	*variable;

	variable = get_env(env, str + 1);
	if (variable && variable == env)
		return (ft_strdup("\0"));
	if (!ft_strcmp(str + 1, "PATH") && !variable)
		variable = env;
	if (!variable)
		str = ft_strdup("\0");
	else
		str = variable->arg;
	str = ft_strjoin("\"", str);
	str = ft_strjoin(str, "\"");
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
