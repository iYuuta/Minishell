#include "../minishell.h"

int check_builtins(t_cmd *cmd)
{
    if (!ft_strcmp(cmd->tokens->token, "env"))
        return (print_env(cmd->env));
    if (!ft_strcmp(cmd->tokens->token, "pwd"))
        return (pwd(cmd->env, 1));
    if (!ft_strcmp(cmd->tokens->token, "unset"))
        return (unset(cmd->tokens), 0);
    if (!ft_strcmp(cmd->tokens->token, "export"))
        return (export(cmd->tokens));
	if (!ft_strcmp(cmd->tokens->token, "exit"))
        return (exit_shell());
    if (!ft_strcmp(cmd->tokens->token, "cd"))
        return (change_directory(cmd->tokens));
	// if (!ft_strcmp(token->token, "echo"))
    //     return (echo_shell(token->next));
    return (2);
}

int execution(char *str, t_env *env)
{
    t_cmd *arg;

    arg = parse_args(str, env);
    if (!arg)
        return (1);
    if (check_builtins(arg) != 2)
        return (0);
    return (0);
}