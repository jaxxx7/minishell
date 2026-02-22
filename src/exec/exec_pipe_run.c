/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/02/15 15:07:46 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

void	print_pipeline_redir_errors(t_cmd *cmds)
{
	while (cmds)
	{
		if (cmds->redir_error && cmds->redir_err_file && cmds->redir_err_msg)
			print_error(cmds->redir_err_file, cmds->redir_err_msg);
		cmds = cmds->next;
	}
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
		child_process_pipe(cmd, pipes, i, data);
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
	close_heredocs(data->cmds);
	close_pipes(pipes, data->count);
	wait_all_children(pids, data->count);
	print_pipeline_redir_errors(data->cmds);
	restore_signals();
	return (0);
}

static int	init_pipe_data(t_pipe_data *data, t_cmd *cmds, char ***env)
{
	data->cmds = cmds;
	data->env = env;
	data->count = count_cmds(cmds);
	data->pipes = allocate_pipes(data->count);
	data->pids = allocate_pids(data->count);
	if (!data->pipes || !data->pids)
	{
		free(data->pipes);
		free(data->pids);
		return (print_error("malloc", "allocation failed"), -1);
	}
	if (create_pipes(data->pipes, data->count) == -1)
	{
		free(data->pipes);
		free(data->pids);
		return (print_error("pipe", "failed to create pipes"), -1);
	}
	return (0);
}

int	execute_pipes(t_cmd *cmds, char ***env)
{
	t_pipe_data	data;
	int			ret;

	if (init_pipe_data(&data, cmds, env) == -1)
		return (1);
	ret = run_all_commands(&data, data.pipes, data.pids);
	free(data.pipes);
	free(data.pids);
	return (ret);
}
