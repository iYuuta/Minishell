#include "../minishell.h"

t_arg	*check_new_line(t_arg *arg, int *new_line)
{
	int	i;
	int tracker;
	t_arg *tmp;

	i = 0;
	tracker = 1;
	tmp = arg;
	while (tmp)
	{
		i = 1;
		if (tmp->type == FLAG && tracker)
		{
			while (tmp->token[i] && tmp->token[i] == 'n')
				i++;
			if (!tmp->token[i])
				*new_line = 1;
			else
				tracker = 0;
		}
		else
			tmp->type = WORD;
		tmp = tmp->next;
	}
	if (!(*new_line))
		return (arg);
	return (NULL);
}

int echo(t_cmd *cmd)
{
	int new_line;
	t_arg *args;

	new_line = 0;
	args = check_new_line(cmd->tokens, &new_line);
	if (args)
		new_line = 1;
	else
		args = cmd->tokens;
	args = args->next;
	while (args)
	{
		ft_putstr_fd(args->token, 1);
		args = args->next;
		if (cmd->tokens)
			write(1, " ", 1);
	}
	if (!new_line)
		printf("\n");
	return (0);
}
