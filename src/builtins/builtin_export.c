/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/02/15 15:26:15 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_export_arg(char *arg, char ***env)
{
	int		i;
	char	*name;
	char	*equal_pos;

	if (!arg || !*arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (print_error_arg("export", arg,
				"not a valid identifier"), 1);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (print_error_arg("export", arg,
					"not a valid identifier"), 1);
		i++;
	}
	equal_pos = ft_strchr(arg, '=');
	if (!equal_pos)
		return (0);
	name = ft_substr(arg, 0, equal_pos - arg);
	if (!name)
		return (1);
	set_env_var(name, equal_pos + 1, env);
	free(name);
	return (0);
}

static void	sort_env(char **sorted, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - 1 - i)
		{
			if (ft_strncmp(sorted[j], sorted[j + 1], ft_strlen(sorted[j])
					+ ft_strlen(sorted[j + 1]) + 1) > 0)
			{
				tmp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_export_line(char *entry)
{
	char	*equal_pos;

	ft_putstr_fd("declare -x ", 1);
	equal_pos = ft_strchr(entry, '=');
	if (!equal_pos)
	{
		ft_putendl_fd(entry, 1);
		return ;
	}
	write(1, entry, equal_pos - entry);
	ft_putstr_fd("=\"", 1);
	ft_putstr_fd(equal_pos + 1, 1);
	ft_putendl_fd("\"", 1);
}

static void	print_export(char **env)
{
	int		i;
	int		count;
	char	**sorted;

	count = 0;
	while (env[count])
		count++;
	sorted = malloc(sizeof(char *) * count);
	if (!sorted)
		return ;
	i = 0;
	while (i < count)
	{
		sorted[i] = env[i];
		i++;
	}
	sort_env(sorted, count);
	i = 0;
	while (i < count)
		print_export_line(sorted[i++]);
	free(sorted);
}

int	builtin_export(char **args, char ***env)
{
	int		i;
	int		ret;

	if (!args[1])
		return (print_export(*env), 0);
	ret = 0;
	i = 1;
	while (args[i])
	{
		if (process_export_arg(args[i], env))
			ret = 1;
		i++;
	}
	return (ret);
}
