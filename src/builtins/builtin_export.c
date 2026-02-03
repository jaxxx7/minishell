/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanisubu <yanisubu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/01/15 10:00:00 by yanisubu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_export(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(env[i], 1);
		i++;
	}
}

static int	process_export_arg(char *arg, char ***env)
{
	char	*name;
	char	*value;
	char	*equal_pos;

	if (!is_valid_identifier(arg))
	{
		print_error_arg("export", arg, "not a valid identifier");
		return (1);
	}
	equal_pos = ft_strchr(arg, '=');
	if (!equal_pos)
		return (0);
	name = ft_substr(arg, 0, equal_pos - arg);
	if (!name)
		return (1);
	value = equal_pos + 1;
	set_env_var(name, value, env);
	free(name);
	return (0);
}

int	builtin_export(char **args, char ***env)
{
	int	i;
	int	ret;

	if (!args[1])
	{
		print_export(*env);
		return (0);
	}
	ret = 0;
	i = 1;
	while (args[i])
	{
		if (process_export_arg(args[i], env) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}
