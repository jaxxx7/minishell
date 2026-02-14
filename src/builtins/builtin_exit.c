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

static long long	parse_number(const char *str, int *i, int sign, int *error)
{
	long long	res;
	int			digit;

	res = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		digit = str[*i] - '0';
		if (sign == 1 && res > (LLONG_MAX - digit) / 10)
		{
			*error = 1;
			return (0);
		}
		if (sign == -1 && - res < (LLONG_MIN + digit) / 10)
		{
			*error = 1;
			return (0);
		}
		res = res * 10 + digit;
		(*i)++;
	}
	return (res * sign);
}

static long long	ft_atoll_safe(const char *str, int *error)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	*error = 0;
	return (parse_number(str, &i, sign, error));
}

int	builtin_exit(char **args)
{
	long long	exit_code;
	int			overflow;

	ft_putendl_fd("exit", 1);
	if (!args[1])
		return (-1);
	exit_code = ft_atoll_safe(args[1], &overflow);
	if (!is_numeric(args[1]) || overflow)
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
	g_exit_status = (int)(exit_code & 255);
	return (-1);
}
