#include "../minishell.h"

int	execute_single_command(t_cmd *cmd)
{
	int	value;

	value = execute_builtins(cmd, cmd->outfile);
	close_files(0, 0);
	return (value);
}

int	child_process(t_cmd *cmd, int *new_pipe, int *prev_pipe_in)
{
	int		value;
	char	**args;
	char	*path;

	child_redirection(cmd, new_pipe, prev_pipe_in);
	if (!cmd->tokens)
		exit(0);
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
	return (exit(value), value);
}

void	execute_command(t_cmd *cmd, int *prev_pipe_in, \
int new_pipe[2], int *fail_status)
{
	int	pid;

	if (check_failure(cmd, &prev_pipe_in, &new_pipe, fail_status))
		return ;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	if (pid == 0 && signal(SIGQUIT, SIG_DFL))
		child_process(cmd, new_pipe, prev_pipe_in);
	else
	{
		save_pid(pid, 0, 1);
		signal(SIGINT, SIG_IGN);
		if (*prev_pipe_in != -1)
			close(*prev_pipe_in);
		if (cmd->next)
			*prev_pipe_in = new_pipe[0];
		if (new_pipe[1] != -1)
			close(new_pipe[1]);
	}
	close_files(0, 0);
}

int	child_wait(void)
{
	int	status;
	int	last_status;
	int	*pid;
	int	i;

	i = -1;
	pid = save_pid(0, 0, 0);
	if (!pid)
		return (1);
	last_status = 0;
	while (pid[++i])
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
		{
			last_status = WEXITSTATUS(status);
			return_value(last_status, 1);
		}
		if (WIFSIGNALED(status))
		{
			last_status = WTERMSIG(status);
			if (last_status == SIGQUIT && !pid[i + 1])
				write(2, "Quit: 3\n", 8);
			return_value(last_status + 128, 1);
		}
	}
	return (last_status);
}

int	execution(char *str, t_env *env)
{
	t_cmd	*cmds;
	int		prev_pipe_in;
	int		new_pipe[2];
	int		fail_status;

	prev_pipe_in = -1;
	new_pipe[0] = -1;
	new_pipe[1] = -1;
	fail_status = -1;
	cmds = parse_args(str, env);
	if (!cmds)
		return (1);
	while (cmds)
	{
		execute_command(cmds, &prev_pipe_in, new_pipe, &fail_status);
		if (cmds->number == 1 && is_builtin(cmds) && !cmds->next)
			return (signal(SIGINT, handle_signales), copy_attributes(0), 0);
		if (g_ctrl == 2)
			break ;
		cmds = cmds->next;
	}
	child_wait();
	if (fail_status != -1)
		return_value(fail_status, 1);
	return (signal(SIGINT, handle_signales), copy_attributes(0), 0);
}
