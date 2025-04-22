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

int execute_command(t_cmd *cmd)
{
	int value;
	int pid;

	if (open_pipes(cmd) || open_files(cmd))
		return (1);
	value = check_builtins(cmd);
	if (value == 2)
	{
		pid = fork();
		value = 0;
		if (pid == 0)
		{
			if (cmd->infile != 0)
			{
				dup2(cmd->infile, 0);
				close(cmd->infile);
			}
			else if (cmd->tube[0] != -1)
			{
				dup2(cmd->tube[0], 0);
				close(cmd->tube[1]);
			}
			if (cmd->outfile != 1)
			{
				dup2(cmd->outfile, 1);
				close(cmd->outfile);
			}
			else if (cmd->next)
			{
				dup2(cmd->next->tube[1], 1);
				close(cmd->next->tube[0]);
			}
			if (execv(get_cmd(cmd), get_args(cmd)) == -1)
			{
				value = 1;
        		perror("execv failed");
				close_files();
				exit(1);
			}
		}
		else 
		{
		waitpid(pid, &value, 0);
		}
	}
    return(close_files() , value);
}

int execution(char *str, t_env *env)
{
    t_cmd *cmds;
	int value;

    cmds = parse_args(str, env);
    if (!cmds)
        return (1);
	while (cmds)
	{
		value = execute_command(cmds);
		return_value(value, 1);
		cmds = cmds->next;
	}
    return (0);
}