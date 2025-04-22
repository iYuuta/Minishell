#include "../minishell.h"

void close_files()
{
	int i;

	i = 2;
	while (++i < 1000)
		close(i);
}

static void print_error(char *str, char *file)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(file, 2);
	ft_putendl_fd(str, 2);
}

void print_erno_error(t_cmd *cmd)
{
	if (errno == EACCES)
		print_error(": Permission denied", cmd->file->file);
	else if (errno == ENOENT)
		print_error(": No such file or directory", cmd->file->file);
	else if (errno == EISDIR)
		print_error(": Is a directory", cmd->file->file);
}

int open_files(t_cmd *cmd)
{
	int tmp;

	while (cmd->file)
	{
		if (cmd->file->type == REDIR_OUT)
		{
			cmd->outfile = open(cmd->file->file, O_TRUNC | O_CREAT | O_WRONLY, 0644);
			if (cmd->outfile == -1)
				return (print_erno_error(cmd), close_files(), return_value(1, 1), 1);
		}
		else if (cmd->file->type == REDIR_IN)
		{
			cmd->infile = open(cmd->file->file, O_RDONLY);
			if (cmd->infile == -1)
				return (print_erno_error(cmd), close_files(), return_value(1, 1), 1);
		}
		if (cmd->file->type == REDIR_APPEND)
		{
			cmd->outfile = open(cmd->file->file, O_APPEND | O_CREAT | O_WRONLY, 0644);
			if (cmd->infile == -1)
				return (print_erno_error(cmd), close_files(), return_value(1, 1), 1);
		}
		cmd->file = cmd->file->next;
	}
	return (0);
}