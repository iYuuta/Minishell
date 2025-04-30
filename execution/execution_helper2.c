#include "../minishell.h"

int	check_failure(t_cmd *cmd, int **prev_pipe, int **new_pipe)
{
	if (open_files(cmd))
		return (close(**prev_pipe), 1);
	if (!cmd->tokens)
		return (close(**prev_pipe), close_files(0, 0), 0);
	if (cmd->next == NULL && cmd->number == 1 && is_builtin(cmd))
		return (return_value(execute_single_command(cmd), 1), 1);
	if (cmd->next && pipe(*new_pipe) < 0)
		return (perror("pipe"), 1);
	return (0);
}

void	child_redirection(t_cmd *cmd, int *new_pipe, int *prev_pipe_in)
{
	if (cmd->infile != 0)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	else if (*prev_pipe_in != -1)
	{
		dup2(*prev_pipe_in, STDIN_FILENO);
		close(*prev_pipe_in);
	}
	if (cmd->outfile != 1)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
		if (new_pipe[0] != -1)
			close(new_pipe[0]);
		if (new_pipe[1] != -1)
			close(new_pipe[1]);
	}
	else if (cmd->next)
	{
		dup2(new_pipe[1], STDOUT_FILENO);
		close(new_pipe[0]);
		close(new_pipe[1]);
	}
}
