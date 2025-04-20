#include "../minishell.h"

int check_builtins(t_cmd *cmd)
{
    if (cmd->tokens && !ft_strcmp(cmd->tokens->token, "env"))
        return (print_env(cmd->env));
    if (cmd->tokens && !ft_strcmp(cmd->tokens->token, "pwd"))
        return (pwd(cmd->env, 1));
    if (cmd->tokens && !ft_strcmp(cmd->tokens->token, "unset"))
        return (unset(cmd->tokens), 0);
    if (cmd->tokens && !ft_strcmp(cmd->tokens->token, "export"))
        return (export(cmd->tokens));
	if (cmd->tokens && !ft_strcmp(cmd->tokens->token, "exit"))
        return (exit_shell());
    if (cmd->tokens && !ft_strcmp(cmd->tokens->token, "cd"))
        return (change_directory(cmd->tokens));
	if (cmd->tokens && !ft_strcmp(cmd->tokens->token, "echo"))
        return (echo(cmd));
    return (2);
}


int execute_command(t_cmd *cmd)
{
	int value;

	if (open_files(cmd))
		return(ft_malloc(0, 0),exit(1), 1);
	if (cmd->outfile != 1)
	{
		dup2(cmd->outfile, 1);
		close(cmd->outfile);
	}
	if (cmd->infile != 0)
	{
		dup2(cmd->infile, 0);
		close(cmd->infile);
	}
	value = check_builtins(cmd);
	if (value == 2)
	{
		value = 0;
		if (execv(get_cmd(cmd), get_args(cmd)) == -1)
		{
			value = 1;
        	perror("execv failed");
		}
	}
    return(close_files() ,ft_malloc(0, 0),exit(0) , value);
}

int execution(char *str, t_env *env)
{
    t_cmd *cmds;
	int pid;

    cmds = parse_args(str, env);
    if (!cmds)
        return (1);
	while (cmds)
	{
		pid = fork();
		if (pid == 0)
		{
			execute_command(cmds);
		}
		cmds = cmds->next;
	}
	waitpid(pid, NULL, 0);
    return (0);
}