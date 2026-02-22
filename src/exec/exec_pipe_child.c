/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:35:00 by mhachem           #+#    #+#             */
/*   Updated: 2026/02/22 16:08:29 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_pipe_builtin_cmd(char *name, char **args, char ***env)
{
	if (ft_strncmp(name, "echo", 5) == 0)
		return (builtin_echo(args));
	if (ft_strncmp(name, "cd", 3) == 0)
		return (builtin_cd(args, env));
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(name, "export", 7) == 0)
		return (builtin_export(args, env));
	if (ft_strncmp(name, "unset", 6) == 0)
		return (builtin_unset(args, env));
	if (ft_strncmp(name, "env", 4) == 0)
		return (builtin_env(args, *env));
	if (ft_strncmp(name, "exit", 5) == 0)
		return (builtin_exit(args));
	return (1);
}

static void	exec_pipe_builtin(t_cmd *cmd, t_pipe_data *data)
{
	int	ret;

	ret = exec_pipe_builtin_cmd(cmd->args[0], cmd->args, data->env);
	if (ret == -1)
		pipe_child_exit(data, get_exit_status());
	pipe_child_exit(data, ret);
}

static void	exec_pipe_external(t_cmd *cmd, t_pipe_data *data)
{
	char	*path;

	path = get_cmd_path(cmd->args[0], *data->env);
	if (!path)
	{
		cmd_not_found(cmd->args[0]);
		pipe_child_exit(data, 127);
	}
	execve(path, cmd->args, *data->env);
	print_exec_error(cmd->args[0], path);
	free(path);
	pipe_child_exit(data, 126);
}

void	pipe_child_exec(t_cmd *cmd, t_pipe_data *data)
{
	if (cmd->redir_error || setup_redirections(cmd) == -1)
		pipe_child_exit(data, 1);
	if (!cmd->args || !cmd->args[0])
		pipe_child_exit(data, 0);
	if (is_builtin(cmd->args[0]))
		exec_pipe_builtin(cmd, data);
	exec_pipe_external(cmd, data);
}
