#include "../minishell.h"

int	is_builtin(t_cmd *cmd)
{
	char	*name;

	name = NULL;
	if (cmd->tokens && cmd->tokens->token)
		name = cmd->tokens->token;
	if (name && (!ft_strcmp(name, "env") || !ft_strcmp(name, "pwd")
			|| !ft_strcmp(name, "unset") || !ft_strcmp(name, "export")
			|| !ft_strcmp(name, "exit")
			|| !ft_strcmp(name, "cd") || !ft_strcmp(name, "echo")))
	{
		return (1);
	}
	return (0);
}

int	execute_builtins(t_cmd *cmd, int fd)
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

char	**get_args(t_cmd *cmds)
{
	char	**args;
	int		count;
	int		i;
	t_arg	*tmp;

	count = 0;
	i = 0;
	tmp = cmds->tokens;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	tmp = cmds->tokens;
	args = ft_malloc(sizeof(char *) * (count + 1), 1);
	args[count] = NULL;
	while (tmp)
	{
		args[i++] = tmp->token;
		tmp = tmp->next;
	}
	return (args);
}

char	*get_cmd(t_cmd *cmd)
{
	char		*tmp;
	char		*command;
	char		**paths;
	t_env		*path;
	struct stat	info;

	stat(cmd->tokens->token, &info);
	if (S_ISDIR(info.st_mode))
		return (NULL);
	if (access(cmd->tokens->token, F_OK | X_OK) == 0)
		return (cmd->tokens->token);
	path = get_env(cmd->env, "PATH");
	if (!path)
		path = cmd->env;
	paths = ft_split(path->arg, ':');
	if (!cmd->tokens->token)
		return (NULL);
	if (!(*cmd->tokens->token))
		return (NULL);
	if (cmd->tokens->token[0] == '/' || cmd->tokens->token[0] == '.')
	{
		if (access(cmd->tokens->token, F_OK | X_OK) == 0)
			return (cmd->tokens->token);
		return (NULL);
	}
	while (paths != NULL && *paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd->tokens->token);
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		paths++;
	}
	*paths = getcwd(NULL, 0);
	tmp = ft_strjoin(*paths, "/");
	command = ft_strjoin(tmp, cmd->tokens->token);
	if (access(command, F_OK | X_OK) == 0)
		return (command);
	return (NULL);
}
