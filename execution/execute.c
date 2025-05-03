#include "../minishell.h"

int	execute_single_command(t_cmd *cmd)
{
	int	value;

	value = execute_builtins(cmd, cmd->outfile);
	return (value);
}

int	child_process(t_cmd *cmd, int *new_pipe, int *prev_pipe_in)
{
	int		value;
	char	**args;
	char	*path;

	child_redirection(cmd, new_pipe, prev_pipe_in);
	if (cmd->tokens && cmd->tokens->token[0] == '\0')
		return (write(2, "minishell: : command not found\n", 31),
			exit(127), 0);
	value = execute_builtins(cmd, 1);
	if (value == 2)
	{
		args = get_args(cmd);
		path = get_cmd(cmd, NULL);
		if (!path || !args || !(*args))
			exit(return_value(0, 0));
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

	if (check_failure(cmd, &prev_pipe_in, &new_pipe))
		return (1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0 && signal(SIGQUIT, SIG_DFL))
		value = child_process(cmd, new_pipe, prev_pipe_in);
	else
	{
		signal(SIGINT, SIG_IGN);
		if (*prev_pipe_in != -1)
			close(*prev_pipe_in);
		if (cmd->next)
			*prev_pipe_in = new_pipe[0];
		if (new_pipe[1] != -1)
			close(new_pipe[1]);
	}
	return (close_files(0, 0), value);
}

int	child_wait(void)
{
	int	status;
	int	last_status;

	last_status = 0;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
		{
			last_status = WEXITSTATUS(status);
			return_value(last_status, 1);
		}
		if (WIFSIGNALED(status))
		{
			last_status = WTERMSIG(status);
			if (last_status == SIGQUIT)
			{
				write(2, "Quit: 3\n", 8);
				last_status = 131;
				return_value(last_status, 1);
			}
		}
	}
	return (last_status);
}

int	execution(char *str, t_env *env)
{
	t_cmd	*cmds;
	int		prev_pipe_in;
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
		last_status = execute_command(cmds, &prev_pipe_in, new_pipe, 0);
		if (cmds->number == 1 && is_builtin(cmds) && !cmds->next)
			return (signal(SIGINT, handle_signales), last_status);
		cmds = cmds->next;
	}
	last_status = child_wait();
	return (signal(SIGINT, handle_signales), copy_attributes(0), last_status);
}
