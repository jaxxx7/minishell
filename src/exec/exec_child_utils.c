/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanisubu <yanisubu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/02/13 10:00:00 by yanisubu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_exit(t_cmd *cmds, char **env, int status)
{
	free_commands(cmds);
	free_env(env);
	exit(status);
}

void	pipe_child_exit(t_pipe_data *data, int status)
{
	free_commands(data->cmds);
	free_env(*data->env);
	free(data->pipes);
	free(data->pids);
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