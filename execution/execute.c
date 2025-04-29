#include "../minishell.h"

int	execute_single_command(t_cmd *cmd)
{
	int	value;

	value = execute_builtins(cmd, cmd->outfile);
	close_files(0, 0);
	return (value);
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

int	child_process(t_cmd *cmd, int *new_pipe, int *prev_pipe_in)
{
	int		value;
	char	**args;
	char	*path;

	child_redirection(cmd, new_pipe, prev_pipe_in);
	if (cmd->tokens && cmd->tokens->token[0] == '\0')
		return (ft_putendl_fd("minishell: : command not found", 2),
			exit(127), 0);
	value = execute_builtins(cmd, 1);
	if (value == 2)
	{
		args = get_args(cmd);
		path = get_cmd(cmd, NULL);
		if (!path || !args || !(*args))
			exit(127);
		execve(path, args, oldenv(NULL));
		strerror(errno);
		ft_malloc(0, 0);
		exit(127);
	}
	else
		exit(value);
	return (value);
}

int	execute_command(t_cmd *cmd, int *prev_pipe_in, int new_pipe[2], int value)
{
	int	pid;

	if (open_files(cmd))
		return (close(*prev_pipe_in), 1);
	if (!cmd->tokens)
		return (close(*prev_pipe_in), close_files(0, 0), 0);
	if (cmd->next == NULL && cmd->number == 1 && is_builtin(cmd))
		return (return_value(execute_single_command(cmd), 1));
	if (cmd->next && pipe(new_pipe) < 0)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0 && signal(SIGQUIT, SIG_DFL) && signal(SIGINT, SIG_DFL))
		value = child_process(cmd, new_pipe, prev_pipe_in);
	else
	{
		if (*prev_pipe_in != -1)
			close(*prev_pipe_in);
		if (cmd->next)
			*prev_pipe_in = new_pipe[0];
		if (new_pipe[1] != -1)
			close(new_pipe[1]);
	}
	return (close_files(0, 0), value);
}

int	execution(char *str, t_env *env)
{
	t_cmd	*cmds;
	int		prev_pipe_in;
	int		status;
	int		last_status;
	int		new_pipe[2];

	prev_pipe_in = -1;
	last_status = 0;
	new_pipe[0] = -1;
	new_pipe[1] = -1;
	cmds = parse_args(str, env);
	if (!cmds)
		return (1);
	while (cmds)
	{
		execute_command(cmds, &prev_pipe_in, new_pipe, 0);
		cmds = cmds->next;
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		return_value(last_status, 1);
	}
	return (copy_attributes(0), last_status);
}
