/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/02/15 14:32:54 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

int	count_cmds(t_cmd *cmds)
{
	int		count;
	t_cmd	*tmp;

	count = 0;
	tmp = cmds;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

t_cmd	*get_cmd_at(t_cmd *cmds, int index)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = cmds;
	while (tmp && i < index)
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}

void	pipe_child_exec(t_cmd *cmd, t_pipe_data *data)
{
	char	*path;
	int		ret;

	if (cmd->redir_error)
		pipe_child_exit(data, 1);
	if (setup_redirections(cmd) == -1)
		pipe_child_exit(data, 1);
	if (!cmd->args || !cmd->args[0])
		pipe_child_exit(data, 0);
	if (is_builtin(cmd->args[0]))
	{
		ret = execute_builtin(cmd, data->env);
		if (ret == -1)
			pipe_child_exit(data, g_exit_status);
		pipe_child_exit(data, ret);
	}
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

int	*allocate_pipes(int count)
{
	int	*pipes;
	int	num_pipes;

	num_pipes = count - 1;
	if (num_pipes <= 0)
		return (NULL);
	pipes = malloc(sizeof(int) * num_pipes * 2);
	if (!pipes)
		return (NULL);
	return (pipes);
}

pid_t	*allocate_pids(int count)
{
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * count);
	if (!pids)
		return (NULL);
	return (pids);
}
