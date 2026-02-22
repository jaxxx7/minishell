/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/02/22 17:00:27 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_stdio_in_child(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void	child_exit(t_cmd *cmds, char **env, int status)
{
	free_commands(cmds);
	free_env(env);
	close_stdio_in_child();
	exit(status);
}

void	pipe_child_exit(t_pipe_data *data, int status)
{
	free_commands(data->cmds);
	free_env(*data->env);
	free(data->pipes);
	free(data->pids);
	close_stdio_in_child();
	exit(status);
}

void	close_heredocs(t_cmd *cmds)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		if (current->heredoc_fd != -1)
			close(current->heredoc_fd);
		current = current->next;
	}
}

void	child_process_pipe(t_cmd *cmd, int *pipes, int i, t_pipe_data *data)
{
	setup_child_signals();
	setup_pipe_child(pipes, i, data->count);
	pipe_child_exec(cmd, data);
}
