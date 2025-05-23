#include "../minishell.h"

int	pwd(t_cmd *cmd)
{
	char	pwd[PATH_MAX];
	char	*back_up;

	if (getcwd(pwd, PATH_MAX))
		ft_putendl_fd(pwd, cmd->outfile);
	else
	{
		back_up = store_pwd(NULL);
		if (!back_up)
			return (ft_putendl_fd("cannot retrieve cwd", 2), 1);
		ft_putendl_fd(back_up, cmd->outfile);
	}
	return (0);
}
