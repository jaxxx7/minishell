/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:35:00 by mhachem           #+#    #+#             */
/*   Updated: 2026/02/15 15:07:46 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_pipe_builtin(t_cmd *cmd, t_pipe_data *data)
{
	int	ret;

	ret = execute_builtin(cmd, data->env);
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
