/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanisubu <yanisubu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/02/03 10:00:00 by yanisubu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static void	child_process(t_cmd *cmd, int *pipes, int i, t_pipe_data *data)
{
	setup_child_signals();
	setup_pipe_child(pipes, i, data->count);
	pipe_child_exec(cmd, data->env);
}

static int	fork_command(t_cmd *cmd, int *pipes, int i, t_pipe_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		print_error("fork", "failed to create process");
		return (-1);
	}
	if (pid == 0)
		child_process(cmd, pipes, i, data);
	return (pid);
}

static int	run_all_commands(t_pipe_data *data, int *pipes, pid_t *pids)
{
	t_cmd	*cmd;
	int		i;

	setup_parent_signals();
	i = 0;
	while (i < data->count)
	{
		cmd = get_cmd_at(data->cmds, i);
		pids[i] = fork_command(cmd, pipes, i, data);
		if (pids[i] == -1)
		{
			close_pipes(pipes, data->count);
			return (-1);
		}
		i++;
	}
	close_pipes(pipes, data->count);
	wait_all_children(pids, data->count);
	restore_signals();
	return (0);
}

static int	init_pipe_data(t_pipe_data *data, t_cmd *cmds, char ***env)
{
	data->cmds = cmds;
	data->env = env;
	data->count = count_cmds(cmds);
	return (0);
}

int	execute_pipes(t_cmd *cmds, char ***env)
{
	t_pipe_data	data;
	int			*pipes;
	pid_t		*pids;
	int			ret;

	init_pipe_data(&data, cmds, env);
	pipes = allocate_pipes(data.count);
	pids = allocate_pids(data.count);
	if (!pipes || !pids)
	{
		free(pipes);
		free(pids);
		return (print_error("malloc", "allocation failed"), 1);
	}
	if (create_pipes(pipes, data.count) == -1)
	{
		free(pipes);
		free(pids);
		return (print_error("pipe", "failed to create pipes"), 1);
	}
	ret = run_all_commands(&data, pipes, pids);
	free(pipes);
	free(pids);
	return (ret);
}
