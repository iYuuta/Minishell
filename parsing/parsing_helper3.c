#include "../minishell.h"

int	is_flag(char *str)
{
	if (!str && !(*str))
		return (0);
	if (*str == '\'' || *str == '\"')
		str++;
	if (*str++ == '-' && *str)
		return (1);
	return (0);
}

int	is_redirection(char *str)
{
	if (!ft_strcmp(str, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(str, ">>"))
		return (REDIR_APPEND);
	if (!ft_strcmp(str, "<"))
		return (REDIR_IN);
	if (!ft_strcmp(str, ">"))
		return (REDIR_OUT);
	return (0);
}

int	is_pipe(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (PIPE);
	return (WORD);
}
