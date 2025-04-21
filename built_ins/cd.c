#include "../minishell.h"

int change_pwd(t_env *env, char *pwd)
{
    t_env *cwdiroctory;

    cwdiroctory = get_env(env, "PWD");
    if (!cwdiroctory)
    {
        cwdiroctory = new_env("PWD");
        if (!cwdiroctory)
            return (1);
        cwdiroctory->arg = ft_env_strdup(pwd);
        if (!cwdiroctory->arg)
            return (1);
    }
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
    {
        oldpwd = new_env("OLDPWD");
        if (!oldpwd)
            return (1);
        oldpwd->arg = ft_env_strdup(str);
        if (!oldpwd->arg)
            return (1);
        env_add_back(&env, oldpwd);
        return (0);
    }
    oldpwd->arg = ft_env_strdup(str);
    if (!oldpwd->arg)
        return (1);
    return (0);
}

int special_case(t_cmd *cmd)
{
    t_env *pwd;

    pwd = get_env(cmd->env, "PWD");
    if (!pwd)
        return (1);
    if (!ft_strcmp(cmd->tokens->next->token, ".."))
    {
        change_pwd(cmd->env, ft_strjoin(pwd->arg, "/.."));
        return (ft_putendl_fd("cd: error retrieving current directory: getcwd:\
            cannot access parent directories: No such file or directory", 2), 1);
    }
}

int change_directory(t_cmd *cmd)
{
    char pwd[PATH_MAX];

    if (!cmd->tokens->next)
        return (ft_putstr_fd("cd only supports relative or absolute path\n", 2), 1);
    if (!getcwd(pwd, PATH_MAX))
        ft_memset(pwd, 0, sizeof(char *));
    if (!pwd)
        return (1);
    cmd->tokens = cmd->tokens->next;
    if (access(cmd->tokens->token, X_OK) == -1)
        return (printf("bash: cd: %s: Permission denied\n", cmd->tokens->token), 1);
    if (chdir(cmd->tokens->token))
        return (printf("bash: cd: %s: No such file or directory\n", cmd->tokens->token), 1);
    if (change_old_pwd(cmd->tokens->env, pwd))
        return (1);
    if (change_pwd(cmd->tokens->env, cmd->tokens->token))
        return (1);
    return (0);
}