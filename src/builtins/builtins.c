/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanisubu <yanisubu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/01/15 10:00:00 by yanisubu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

static int	execute_builtin_cmd(char *cmd, char **args, char ***env)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (builtin_echo(args));
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (builtin_cd(args, env));
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (builtin_export(args, env));
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (builtin_unset(args, env));
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (builtin_env(*env));
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (builtin_exit(args));
	return (1);
}

int	execute_builtin(t_cmd *cmd, char ***env)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (setup_redirections(cmd) == -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	ret = execute_builtin_cmd(cmd->args[0], cmd->args, env);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	restore_signals();
	return (ret);
}
