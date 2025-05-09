#include "../minishell.h"

int	is_after_pipe(char *str, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_strchr("\'\"", str[i]))
		{
			j = get_index(str, str[i]);
			if (j == -1)
				return (0);
			i += j;
		}
		if (str[i] == '|' && i < index)
			return (1);
		i++;
	}
	return (0);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*node;

	node = ft_malloc(sizeof(t_cmd), 1);
	node->infile = 0;
	node->outfile = 1;
	node->tokens = NULL;
	node->next = NULL;
	return (node);
}

int	polished_strlen(char *token)
{
	int		len;
	int		i;
	char	c;

	i = 0;
	len = 0;
	c = 0;
	while (token[i])
	{
		if (c != 0 && token[i] == c)
		{
			len++;
			c = 0;
		}
		else if (c == 0 && (token[i] == '\'' || token[i] == '\"')
			&& get_index(token + i, token[i]) != -1)
		{
			len++;
			c = token[i];
		}
		i++;
	}
	return (i - len);
}

char	*polish(char *token)
{
	int		len;
	int		i;
	char	quote;
	char	*new_token;

	if (*token == '\"' && token[ft_strlen(token) - 1] == '\"')
		safe_trim(token);
	len = polished_strlen(token);
	i = 0;
	new_token = ft_malloc(len + 1, 1);
	new_token[len] = '\0';
	quote = 0;
	while (i < len)
	{
		if (quote == 0 && (*token == '\'' || *token == '\"')
			&& get_index(token, *token) != -1)
			quote = *token;
		else if (quote != 0 && quote == *token)
			quote = 0;
		else
			new_token[i++] = *token;
		token++;
	}
	return (new_token);
}
