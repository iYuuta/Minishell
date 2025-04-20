#include "../minishell.h"

int change_pwd(t_env *env)
{
    char *pwd;
    t_env *cwdiroctory;

    pwd = getcwd(NULL, 0);
    if (!pwd)
        return (1);
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

int change_directory(t_arg *arg)
{
    char *pwd;

    pwd = getcwd(NULL, 0);
    if (!pwd)
        return (1);
    if (!arg->next || arg->next->type != WORD)
        return (ft_putstr_fd("cd only supposts relative or absolute path\n", 2), 1);
    arg = arg->next;
    if (access(arg->token, X_OK) == -1)
        return (printf("bash: cd: %s: Permission denied\n", arg->token), 1);
    if (chdir(arg->token))
        return (printf("bash: cd: %s: No such file or directory\n", arg->token), 1);
    if (change_old_pwd(arg->env, pwd))
        return (1);
    if (change_pwd(arg->env))
        return (1);
    return (0);
}