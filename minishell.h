#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft_dyali/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <termios.h>

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define DEF_PATH "/usr/local/bin:/usr/bin:/bin:/\
usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin"

extern int	g_ctrl;

typedef enum e_token_type
{
	WORD,
	CMD,
	file,
	FLAG,
	PIPE,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_IN,
	HEREDOC,
}		t_token_type;

typedef struct s_malloc
{
	void			*ptr;
	struct s_malloc	*next;
}		t_malloc;

typedef struct s_env
{
	char			*name;
	char			*arg;
	struct s_env	*prev;
	struct s_env	*next;
}		t_env;

typedef struct s_arg
{
	char			*token;
	int				type;
	struct s_env	*env;
	struct s_arg	*next;
	struct s_arg	*prev;
	struct s_arg	*head;
}		t_arg;

typedef struct s_file
{
	char			*file;
	int				type;
	struct s_file	*next;
}		t_file;

typedef struct s_command
{
	struct s_arg		*tokens;
	struct s_file		*file;
	struct s_env		*env;
	int					number;
	int					infile;
	int					outfile;
	struct s_command	*next;
}	t_cmd;

/************** signals **************/

void	handle_signales(int signal);

/*************************************/

/************* execution *************/

int		execution(char *str, t_env *env);
int		open_files(t_cmd *cmd);
void	close_files(int file, int flag);
char	*get_cmd(t_cmd *cmd, char *tmp);
char	**get_args(t_cmd *cmds);
void	command_error(char *str, char *file);
void	child_redirection(t_cmd *cmd, int *new_pipe, int *prev_pipe_in);
int		check_failure(t_cmd *cmd, int **prev_pipe, \
int **new_pipe, int *fail_status);
int		execute_single_command(t_cmd *cmd);

/*************************************/

/************** builtins *************/

int		print_env(t_env *env, t_cmd *cmd);
int		pwd(t_cmd *cmd);
int		unset(t_arg *arg);
int		export(t_cmd *token);
int		exit_shell(t_cmd *arg);
int		change_directory(t_cmd *arg);
int		echo(t_cmd *cmd);
int		is_builtin(t_cmd *cmd);
int		execute_builtins(t_cmd *cmd, int fd);
int		change_old_pwd(t_env *env, char *str);
t_env	*env_head(t_env *env);

/*************************************/

/************** parsing **************/

t_cmd	*parse_args(char *str, t_env *env);
int		is_flag(char *str);
t_arg	*split_args(char *str, t_env *env);
char	*polish(char *token);
int		identify_tokens(t_arg *token);
char	*read_here_doc(char *token, t_env *env);
int		is_redirection(char *str);
int		get_index(char *str, char c);
char	*expand_vars(t_env *env, char *str, int exp);
t_cmd	*finish_parse(t_arg *args, t_env *env);
char	*expand_str(char *str, t_env *env, int *i, int skip);
int		get_files(t_arg *token, t_cmd **node);
void	cmd_add_back(t_cmd **lst, t_cmd *new);
t_arg	*copy_token(t_arg *token);
char	*expand_heredoc(t_env *env, char *str);
t_arg	*handle_redir(t_arg *token);
t_arg	*refine_token(t_arg *token);
int		is_pipe(char *str);
int		check_quotes(char *str);
char	*safe_expand(char *str);
char	*safe_trim(char *str);
int		syntax_error(char *str, t_env *env);
t_cmd	*new_cmd(void);

/*************************************/

/************** envirement ***********/

t_env	*env_init(char **env, t_env *head, int i);
char	*ft_env_sub(char const *s, unsigned int start, size_t len);
char	*ft_env_strdup(const char *s1);
char	*ft_env_join(char *s1, char const *s2);
t_env	*add_to_env(t_env *env, char *var);
t_env	*new_env(char *content);
t_env	*last_env(t_env *lst);
void	env_add_back(t_env **lst, t_env *new);
int		return_value(int value, int flag);

/*************************************/

/************** helper ***************/

void	*env_malloc(size_t size, int flag);
void	*ft_malloc(size_t size, int flag);
void	*env_malloc(size_t size, int flag);
t_arg	*ft_lstnew(void *content);
void	ft_lstadd_back(t_arg **lst, t_arg *new);
int		ft_lstsize(t_arg *lst);
t_arg	*ft_lstlast(t_arg *lst);
int		sort_export(t_cmd *token);
int		check_export_error(char *str);
int		export_wt_args(t_cmd *arg);
t_env	*get_env(t_env *env, char *name);
int		is_exit_valid(char *str);
char	**oldenv(char **env);
char	*store_pwd(char *pwd);
void	copy_attributes(int flag);
int		*save_pid(int pid, int size, int flag);

/*********************************** */

#endif
