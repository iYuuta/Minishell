#include "../minishell.h"

int	exit_shell()
{
	ft_malloc(0, 0);
	env_malloc(0, 0);
	exit(128);
	return (0);
}