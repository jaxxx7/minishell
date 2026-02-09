/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanisubu <yanisubu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/01/15 10:00:00 by yanisubu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

int	builtin_exit(char **args)
{
	int	exit_code;

	ft_putendl_fd("exit", 1);
	if (!args[1])
		return (-1);
	if (!is_numeric(args[1]))
	{
		print_error_arg("exit", args[1], "numeric argument required");
		g_exit_status = 2;
		return (-1);
	}
	if (count_args(args) > 2)
	{
		print_error("exit", "too many arguments");
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	g_exit_status = exit_code & 255;
	return (-1);
}
