#include "../minishell.h"

void close_files(int file, int flag)
{
    static int *fd;
    static int index;
    int i;

    i = -1;
    if (flag && !fd)
        fd = malloc(sizeof(int) * 1024);
	if (flag && !fd)
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
		return ;
    }
    fd[index] = file;
    index++;
}

static void print_error(char *str, char *file)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(file, 2);
	ft_putendl_fd(str, 2);
}

void print_erno_error(t_cmd *cmd)
{
	if (errno == EACCES)
		print_error(": Permission denied", cmd->file->file);
	else if (errno == ENOENT)
		print_error(": No such file or directory", cmd->file->file);
	else if (errno == EISDIR)
		print_error(": Is a directory", cmd->file->file);
}

int open_files(t_cmd *cmd)
{
	int tmp;

	while (cmd->file)
	{
		if (cmd->file->type == REDIR_OUT)
		{
			tmp = open(cmd->file->file, O_TRUNC | O_CREAT | O_WRONLY, 0644);
			cmd->outfile = tmp;
			if (cmd->outfile == -1)
				return (print_erno_error(cmd), close_files(0, 0), return_value(1, 1), 1);
		}
		else if (cmd->file->type == REDIR_IN)
		{
			tmp = open(cmd->file->file, O_RDONLY);
			cmd->infile = tmp;
			if (cmd->infile == -1)
				return (print_erno_error(cmd), close_files(0, 0), return_value(1, 1), 1);
		}
		if (cmd->file->type == REDIR_APPEND)
		{
			tmp = open(cmd->file->file, O_APPEND | O_CREAT | O_WRONLY, 0644);
			cmd->outfile = tmp;
			if (cmd->infile == -1)
				return (print_erno_error(cmd), close_files(0, 0), return_value(1, 1), 1);
		}
		if (cmd->file->type == HEREDOC)
		{
			cmd->infile = open(".HEREDOC.txt", O_CREAT | O_RDWR, 0666);
			if (cmd->infile == -1)
				return (print_erno_error(cmd), close_files(0, 0), return_value(1, 1), 1);
			write(cmd->infile, cmd->file->file, ft_strlen(cmd->file->file));
			close(cmd->infile);
			tmp = open(".HEREDOC.txt", O_RDWR, 0666);
			cmd->infile = tmp;
			if (cmd->infile == -1)
				return (print_erno_error(cmd), close_files(0, 0), return_value(1, 1), 1);
			unlink(".HEREDOC.txt");
		}
		close_files(tmp, 1);
		cmd->file = cmd->file->next;
	}
	return (0);
}
