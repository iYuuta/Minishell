#include "../minishell.h"

int change_pwd(t_env *env, char *pwd)
{
    t_env *cwdiroctory;

    store_pwd(pwd);
    cwdiroctory = get_env(env, "PWD");
    if (!cwdiroctory)
        return (0);
    cwdiroctory->arg = ft_env_strdup(pwd);
    if (!cwdiroctory->arg)
            return (1);
    return (0);
}

int change_old_pwd(t_env *env, char *str)
{
    t_env *oldpwd;

    oldpwd = get_env(env, "OLDPWD");
    if (!oldpwd)
        return (0);
    oldpwd->arg = ft_env_strdup(str);
    if (!oldpwd->arg)
        return (1);
    return (0);
}

int special_case(t_cmd *cmd)
{
    char *pwd;

    pwd = store_pwd(NULL);
    if (!ft_strcmp(cmd->tokens->next->token, ".."))
    {
        if (chdir(cmd->tokens->next->token))
            return (0);
        change_pwd(cmd->env, ft_strjoin(pwd, "/.."));
        if (!getcwd(NULL, 0))
            ft_putendl_fd("cd: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory", 2);
    }
    return (0);
}

static void printf_error(char *file, char *str)
{
    ft_putstr_fd("minishell: cd: ", 2);
    ft_putstr_fd(file, 2);
    ft_putendl_fd(str, 2);
}

int check_file(char *file)
{
    struct stat info;

    if (stat(file, &info) == -1)
    {
        perror(file);
        return (0);
    }
    if (!S_ISDIR(info.st_mode))
    {
        printf_error(file, ": Not a directory");
        return (0);
    }
    if (access(file, X_OK))
    {
        printf_error(file, ": Permission denied");
        return (0);
    }
    return (1);
}

int change_directory(t_cmd *cmd)
{
    char pwd[PATH_MAX];
    int type;

    if (!cmd->tokens->next)
        return (ft_putstr_fd("cd only supports relative or absolute path\n", 2), 1);
    if (cmd->tokens->next->next)
        return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
    if (!getcwd(pwd, PATH_MAX))
        return (special_case(cmd));
    cmd->tokens = cmd->tokens->next;
    if (!check_file(cmd->tokens->token))
        return (1);
    if (chdir(cmd->tokens->token))
        return (printf_error(cmd->tokens->token, " No such file or directory"), 1);
    if (change_old_pwd(cmd->tokens->env, pwd))
        return (1);
    getcwd(pwd, PATH_MAX);
    if (change_pwd(cmd->tokens->env, pwd))
        return (1);
    return (0);
}
