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

int execution(char *str, t_env *env)
{
    t_cmd *cmds;
	int pid;

    cmds = parse_args(str, env);
    if (!cmds)
        return (1);
	// while (cmds)
	// {
	// 	pid = fork;
	// 	cmds = cmds->next;
	// }
    if (check_builtins(cmds) != 2)
        return (0);
    return (0);
}