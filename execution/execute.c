#include "../minishell.h"

int check_builtins(t_cmd *cmd)
{
	if (cmd->tokens && !ft_strcmp(cmd->tokens->token, "env"))
		return (print_env(cmd->env, cmd));
	if (cmd->tokens && !ft_strcmp(cmd->tokens->token, "pwd"))
		return (pwd(cmd->env, cmd));
	if (cmd->tokens && !ft_strcmp(cmd->tokens->token, "unset"))
		return (unset(cmd->tokens), 0);
	if (cmd->tokens && !ft_strcmp(cmd->tokens->token, "export"))
		return (export(cmd));
	if (cmd->tokens && !ft_strcmp(cmd->tokens->token, "exit"))
		return (exit_shell(cmd->tokens));
	if (cmd->tokens && !ft_strcmp(cmd->tokens->token, "cd"))
		return (change_directory(cmd));
	if (cmd->tokens && !ft_strcmp(cmd->tokens->token, "echo"))
		return (echo(cmd));
	return (2);
}

int	open_pipes(t_cmd *cmd)
{
	if (cmd->next == NULL)
		return (0);
	if (pipe(cmd->next->tube) < 0)
		return (perror("Pipe"), 1);
	return (0);
}

void close_all_pipes(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->tube[0] != -1) close(cmd->tube[0]);
		if (cmd->tube[1] != -1) close(cmd->tube[1]);
		cmd = cmd->next;
	}
}

int execute_command(t_cmd *cmd, int *prev_pipe_in)
{
	int pid;
	if (open_files(cmd))
		return (1);
	int value = check_builtins(cmd);
	int new_pipe[2];

	new_pipe[0] = -1;
	new_pipe[1] = -1;

	if (cmd->next && pipe(new_pipe) < 0)
		return (perror("pipe"), 1);
	if (value == 2)
	{
		pid = fork();
		if (pid < 0)
			return (perror("fork"), 1);
		if (pid == 0)
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
			close_all_pipes(cmd);
			char **args = get_args(cmd);
			char *path = get_cmd(cmd);
			execve(path, args, oldenv(NULL));
			perror("execve");
			exit(127);
		}
		else
		{
			if (*prev_pipe_in != -1)
				close(*prev_pipe_in);
			if (cmd->next)
				*prev_pipe_in = new_pipe[0];
			if (new_pipe[1] != -1)
				close(new_pipe[1]);
		}
	}
	else
	{
		if (*prev_pipe_in != -1)
			close(*prev_pipe_in);
		if (new_pipe[0] != -1) close(new_pipe[0]);
		if (new_pipe[1] != -1) close(new_pipe[1]);
	}
	return (value);
}

int execution(char *str, t_env *env)
{
	t_cmd *cmds = parse_args(str, env);
	t_cmd *current = cmds;
	int prev_pipe_in = -1;
	int status;
	int last_status = 0;

	if (!cmds)
		return 1;
	while (current)
	{
		last_status = execute_command(current, &prev_pipe_in);
		current = current->next;
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
	}
	return_value(last_status, 1);
	return (last_status);
}
