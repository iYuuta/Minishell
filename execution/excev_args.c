#include "../minishell.h"

char **get_args(t_cmd *cmds)
{
	char **args;
	int count;
	int i;
	t_arg *tmp;

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
	char	*tmp;
	char	*command;
	char	**paths;
	t_env *PATH;

	PATH = get_env(cmd->env, "PATH");
	if (!PATH)
		PATH = cmd->env;
	paths = ft_split(PATH->arg, ':');
	if (!cmd->tokens->token || !(*cmd->tokens->token))
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
	return (ft_putstr_fd(cmd->tokens->token, 2), ft_putendl_fd(": command not found", 2), NULL);
}
