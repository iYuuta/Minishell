#include "../minishell.h"

int	over_write(t_env *arg, char *value, int append)
{
	t_env	*new;

	if (append)
	{
		if (!value)
			value = ft_env_strdup("");
		arg->arg = ft_env_join(arg->arg, value);
		if (!arg->arg)
			return (1);
		return (0);
	}
	arg->arg = ft_env_strdup(value);
	if (!arg->arg)
		return (1);
	return (0);
}

int	add_env(t_env **env, char *value, char *name)
{
	t_env	*new;

	new = new_env(name);
	if (!new)
		return (1);
	new->arg = ft_env_strdup(value);
	env_add_back(env, new);
	return (0);
}

static void	print_error(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	export_w_args(t_cmd *cmd, int append, int len)
{
	char	*arg[2];

	if (len > 0 && cmd->tokens->token[len - 1] == '+')
		append = 1;
	arg[0] = ft_env_sub(cmd->tokens->token, 0, len - append);
	if (check_export_error(arg[0]))
		return (print_error(cmd->tokens->token), 1);
	if ((len + 1) != ft_strlen(cmd->tokens->token))
		arg[1] = ft_env_sub(cmd->tokens->token,
				len + 1, ft_strlen(cmd->tokens->token + len + 1));
	else
		arg[1] = ft_env_strdup("");
	if (ft_strchr(arg[1], '$'))
		arg[1] = expand_vars(cmd->env, arg[1], 1);
	arg[1] = polish(arg[1]);
	if (!arg[1])
		return (1);
	if (!get_env(cmd->env, arg[0]))
		append = add_env(&(cmd->env), arg[1], arg[0]);
	else
		append = over_write(get_env(cmd->env, arg[0]), arg[1], append);
	if (append)
		return (1);
	return (0);
}

int	export(t_cmd *cmd)
{
	int	len;
	int	append;

	append = 0;
	if (!cmd->tokens->next)
		sort_export(cmd);
	cmd->tokens = cmd->tokens->next;
	while (cmd->tokens && cmd->tokens->type == WORD)
	{
		len = get_index(cmd->tokens->token, '=');
		if (len == -1)
		{
			if (!get_env(cmd->env, cmd->tokens->token))
				if (export_wt_args(cmd))
					return (1);
		}
		else
			if (export_w_args(cmd, append, len))
				return (1);
		cmd->tokens = cmd->tokens->next;
	}
	return (0);
}
