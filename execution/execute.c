#include "../minishell.h"

int is_builtin(t_cmd *cmd)
{
	char *name;

	name = NULL;
	if (cmd->tokens && cmd->tokens->token)
		name = cmd->tokens->token;
	if (name && (!ft_strcmp(name, "env") || !ft_strcmp(name, "pwd") || 
	!ft_strcmp(name, "unset") || !ft_strcmp(name, "export") || !ft_strcmp(name, "exit") 
	|| !ft_strcmp(name, "cd") || !ft_strcmp(name, "echo")))
	{
		return (1);
	}
	return (0);
}

int execute_builtins(t_cmd *cmd, int fd)
{
	cmd->outfile = fd;
	if (cmd->tokens && !ft_strcmp(cmd->tokens->token, "env"))
		return (print_env(cmd->env, cmd));
	if (cmd->tokens && !ft_strcmp(cmd->tokens->token, "pwd"))
		return (pwd(cmd->env, cmd));
	if (cmd->tokens && !ft_strcmp(cmd->tokens->token, "unset"))
		return (unset(cmd->tokens), 0);
	if (cmd->tokens && !ft_strcmp(cmd->tokens->token, "export"))
		return (export(cmd));
	if (cmd->tokens && !ft_strcmp(cmd->tokens->token, "exit"))
		return (exit_shell(cmd));
	if (cmd->tokens && !ft_strcmp(cmd->tokens->token, "cd"))
		return (change_directory(cmd));
	if (cmd->tokens && !ft_strcmp(cmd->tokens->token, "echo"))
		return (echo(cmd));
	return (2);
}

int execute_single_command(t_cmd *cmd)
{
	int value;

	value = execute_builtins(cmd, cmd->outfile);
	close_files(0, 0);
	return (value);
}

int execute_command(t_cmd *cmd, int *prev_pipe_in)
{
	int pid;
	if (open_files(cmd))
		return (1);
	if (!cmd->tokens)
		return (0);
	if (cmd->next == NULL && cmd->number == 1 && is_builtin(cmd))
		return (execute_single_command(cmd));
	int value;
	int new_pipe[2];

	new_pipe[0] = -1;
	new_pipe[1] = -1;
	value = 0;
	if (cmd->next && pipe(new_pipe) < 0)
		return (perror("pipe"), 1);
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
			value = execute_builtins(cmd, 1);
			if (value == 2)
			{
				char **args = get_args(cmd);
				char *path = get_cmd(cmd);
				if (!path || !args || !(*args))
					exit(127);
				execve(path, args, oldenv(NULL));
				perror("execve");
				exit(127);
			}
			else
				exit(0);
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
	return (close_files(0, 0), value);
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
