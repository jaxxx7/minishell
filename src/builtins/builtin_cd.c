/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanisubu <yanisubu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/01/15 10:00:00 by yanisubu         ###   ########.fr       */
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

	path = get_cd_path(args, env);
	if (!path)
		return (1);
	update_oldpwd(env);
	if (chdir(path) == -1)
	{
		print_error_arg("cd", args[1], "No such file or directory");
		return (1);
	}
	update_pwd(env);
	return (0);
}
