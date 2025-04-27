#include "../minishell.h"

void	new_line_loop(t_arg *tmp, int *new_line, int *tracker)
{
	int	i;

	i = 0;
	while (tmp)
	{
		i = 1;
		if (tmp->type == FLAG && *tracker)
		{
			while (tmp->token[i] && tmp->token[i] == 'n')
				i++;
			if (tmp->token[i] == '\0')
				*new_line = 1;
			else
			{
				*tracker = 0;
				tmp->type = WORD;
			}
		}
		else
		{
			tmp->type = WORD;
			*tracker = 0;
		}
		tmp = tmp->next;
	}
}

t_arg	*check_new_line(t_arg *arg, int *new_line)
{
	int		tracker;
	t_arg	*tmp;

	tracker = 1;
	tmp = arg->next;
	new_line_loop(tmp, new_line, &tracker);
	if (*new_line)
		return (arg);
	return (NULL);
}

int	echo(t_cmd *cmd)
{
	int		new_line;
	t_arg	*args;

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
				write(cmd->outfile, " ", 1);
		}
		args = args->next;
	}
	if (!new_line)
		write(cmd->outfile, "\n", 1);
	return (0);
}
