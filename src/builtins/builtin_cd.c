/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/02/22 15:52:09 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwd(char ***env)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (-1);
	set_env_var("PWD", cwd, env);
	return (0);
}

static int	update_oldpwd(char ***env)
{
	char	*pwd;

	pwd = get_env_val("PWD", *env);
	if (pwd)
		set_env_var("OLDPWD", pwd, env);
	return (0);
}

static char	*get_cd_path(char **args, char ***env)
{
	char	*path;

	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0)
	{
		path = get_env_val("HOME", *env);
		if (!path)
		{
			print_error("cd", "HOME not set");
			return (NULL);
		}
		return (path);
	}
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_env_val("OLDPWD", *env);
		if (!path)
		{
			print_error("cd", "OLDPWD not set");
			return (NULL);
		}
		ft_putendl_fd(path, 1);
		return (path);
	}
	return (args[1]);
}

int	builtin_cd(char **args, char ***env)
{
	char	*path;
	char	*path_dup;
	char	*home;

	if (args[1] && args[2])
		return (error_return("cd", "too many arguments", 1));
	path_dup = NULL;
	if (args[1] && args[1][0] == '~' && args[1][1] == '/')
	{
		home = get_env_val("HOME", *env);
		if (!home)
			return (print_error("cd", "HOME not set"), 1);
		path_dup = ft_strjoin(home, args[1] + 1);
	}
	else
	{
		path = get_cd_path(args, env);
		if (!path)
			return (1);
		path_dup = ft_strdup(path);
	}
	if (!path_dup)
		return (error_return("cd", "memory allocation error", 1));
	if (chdir(path_dup) == -1)
	{
		print_error_arg("cd", args[1], "No such file or directory");
		free(path_dup);
		return (1);
	}
	update_oldpwd(env);
	update_pwd(env);
	free(path_dup);
	return (0);
}
