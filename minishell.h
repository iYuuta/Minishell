#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft_dyali/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <stdio.h>

#define fail 1
#define success 0

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
	HEREDOCTEXT,
	DQUOTE_STRING,
	SQUOTE_STRING,
	VARIABLE,
	VAR_ASSING,
	BACKGROUND,
}   t_token_type;

typedef struct s_malloc
{
	void *ptr;
	struct s_malloc *next;
}           t_malloc;


typedef struct s_env
{
	char *name;
	char *arg;
	struct s_env *prev;
	struct s_env *next;
}           t_env;

typedef struct s_arg
{
	char *token;
	int  type;
	struct s_env *env;
	struct s_arg *next;
	struct s_arg *prev;
	struct s_arg *head;
}           t_arg;

typedef struct s_file
{
	char *file;
	int type;
	struct s_file *next;
}		t_file;

typedef struct s_command
{
	struct s_arg		*tokens;
	struct s_file		*file;
	struct s_env		*env;
	int					infile;
	int					outfile;
	int					append;
	struct	s_command	*next;
}	t_cmd;

/************** signals **************/

void	handle_signales(int signal);

/*************************************/

/************* execution *************/

int execution(char *str, t_env *env);
int	init_commands(t_arg *arg, t_cmd **cmds_head);

/*************************************/

/************** builtins *************/

int		print_env(t_env *env);
int		pwd(t_env *env, int fd);
int		unset(t_arg *arg);
int		export(t_arg *arg);
int		exit_shell();
int		change_directory(t_arg *arg);
int		echo(t_cmd *cmd);
/*************************************/

/************** parsing **************/

t_cmd *parse_args(char *str, t_env *env);
int is_operator(char *str);
int is_flag(char *str);
char **split_args(char *str, int *size);
void polish(t_arg *token);
t_arg *tokenize_arg(char **av, t_env*env);
t_arg *read_here_doc(t_arg *token);
int check_uncompleted_cmd(t_arg *token);
int is_redirection(char *str);
int get_index(char *str, char c);
char *expand_vars(char *token, t_env *env);
t_cmd *finish_parse(t_arg *args, t_env *env);

/*************************************/

/************** envirement ***********/

t_env *env_init(char **env);
char	*ft_env_substr(char const *s, unsigned int start, size_t len);
char	*ft_env_strdup(const char *s1);
char *ft_env_join(char *s1, char const *s2);
t_env *add_to_env(t_env *env, char *var);
t_env	*new_env(char *content);
t_env	*last_env(t_env *lst);
void	env_add_back(t_env **lst, t_env *new);
t_env *change_env(t_env *env);

/*************************************/

/************** helper ***************/

void *env_malloc(size_t size, int flag);
void *ft_malloc(size_t size, int flag);
void *env_malloc(size_t size, int flag);
t_arg	*ft_lstnew(void *content);
void	ft_lstadd_back(t_arg **lst, t_arg *new);
int	ft_lstsize(t_arg *lst);
t_arg	*ft_lstlast(t_arg *lst);
int     sort_export(t_arg *token);
int check_export_error(char *str);
int export_wt_args(t_arg *arg);
t_env *get_env(t_env *env, char *name);

/*********************************** */


#endif
