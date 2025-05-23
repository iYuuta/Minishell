#include "../minishell.h"

void	close_files(int file, int flag)
{
	static int	*fd;
	static int	index;
	int			i;

	i = -1;
	if (!fd)
		fd = ft_malloc(sizeof(int) * 1024, 1);
	if (!fd)
	{
		ft_putendl_fd("malloc failed", 2);
		ft_malloc(0, 0);
		env_malloc(0, 0);
		exit(1);
	}
	if (!flag)
	{
		while (++i < index)
			close(fd[i]);
		index = 0;
		fd = NULL;
		return ;
	}
	fd[index] = file;
	index++;
}

void	command_error(char *str, char *file)
{
	write(2, "minishell: ", 11);
	if (!ft_strcmp(str, "Permission denied")
		|| !ft_strcmp(str, "Is a directory"))
		return_value(126, 1);
	else
		return_value(127, 1);
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void	p_erno(t_cmd *cmd)
{
	if (errno == EACCES)
		command_error("Permission denied", cmd->file->file);
	else if (errno == ENOENT)
		command_error("No such file or directory", cmd->file->file);
	else if (errno == EISDIR)
		command_error("Is a directory", cmd->file->file);
}

int	check_other_cases(t_cmd *cmd, int *tmp, int pipe[2])
{
	if (cmd->file->type == REDIR_APPEND)
	{
		*tmp = open(cmd->file->file, O_APPEND | O_CREAT | O_WRONLY, 0644);
		cmd->outfile = *tmp;
		if (*tmp == -1)
			return (p_erno(cmd), close_files(0, 0), return_value(1, 1), 1);
	}
	if (cmd->file->type == HEREDOC)
	{
		cmd->file->file = read_here_doc(cmd->file->file, cmd->env, pipe);
		if (!(cmd->file->file))
			return (1);
		cmd->infile = open("/tmp/.HEREDOC.txt", O_CREAT | O_WRONLY, 0666);
		if (cmd->infile == -1)
			return (p_erno(cmd), close_files(0, 0), return_value(1, 1), 1);
		write(cmd->infile, cmd->file->file, ft_strlen(cmd->file->file));
		close(cmd->infile);
		*tmp = open("/tmp/.HEREDOC.txt", O_RDONLY);
		cmd->infile = *tmp;
		if (*tmp == -1)
			return (p_erno(cmd), close_files(0, 0), return_value(1, 1), 1);
		unlink("/tmp/.HEREDOC.txt");
	}
	return (0);
}

int	open_files(t_cmd *cmd, int pipe[2])
{
	int	tmp;

	while (cmd->file)
	{
		if (cmd->file->type == REDIR_OUT)
		{
			tmp = open(cmd->file->file, O_TRUNC | O_CREAT | O_WRONLY, 0644);
			cmd->outfile = tmp;
			if (cmd->outfile == -1)
				return (p_erno(cmd), close_files(0, 0), return_value(1, 1), 1);
		}
		else if (cmd->file->type == REDIR_IN)
		{
			tmp = open(cmd->file->file, O_RDONLY);
			cmd->infile = tmp;
			if (cmd->infile == -1)
				return (p_erno(cmd), close_files(0, 0), return_value(1, 1), 1);
		}
		if (check_other_cases(cmd, &tmp, pipe))
			return (1);
		close_files(tmp, 1);
		cmd->file = cmd->file->next;
	}
	return (0);
}
