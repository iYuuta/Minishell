#include "../minishell.h"


t_arg	*check_new_line(t_arg *arg, int *new_line)
{
	int	i;
	int tracker;
	t_arg *tmp;

	i = 0;
	tracker = 1;
	tmp = arg->next;
	while (tmp)
	{
		i = 1;
		if (tmp->type == FLAG && tracker)
		{
			while (tmp->token[i] && tmp->token[i] == 'n')
				i++;
			if (tmp->token[i] == '\0')
				*new_line = 1;
			else
			{
				tracker = 0;
				tmp->type = WORD;
			}
		}
		else
		{
			tmp->type = WORD;
			tracker = 0;
		}
		tmp = tmp->next;
	}
	if (*new_line)
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
		if (args->type == WORD)
		{
			ft_putstr_fd(args->token, cmd->outfile);
			if (args->next)
				write(1, " ", cmd->outfile);
		}
		args = args->next;
	}
	if (!new_line)
		write(1, "\n", cmd->outfile);
	return (0);
}
