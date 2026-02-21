/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanisubu <yanisubu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/01/15 10:00:00 by yanisubu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (i > 1);
}

static int	skip_n_flags(char **args)
{
	int	i;

	i = 1;
	while (args[i] && is_n_flag(args[i]))
		i++;
	return (i);
}

static void	echo_print_arg(char *arg)
{
	char		*san;
	int			len;

	len = get_stripped_len(arg);
	san = fill_stripped(arg, len);
	if (san)
	{
		ft_putstr_fd(san, 1);
		free(san);
	}
	else
		ft_putstr_fd(arg, 1);
}

int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	if (args[1] && is_n_flag(args[1]))
	{
		newline = 0;
		i = skip_n_flags(args);
	}
	while (args[i])
	{
		echo_print_arg(args[i]);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
