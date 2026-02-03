/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanisubu <yanisubu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/01/15 10:00:00 by yanisubu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static void	close_pipes(int *pipes, int count)
{
	int	i;

	i = 0;
	while (i < count * 2)
	{
		close(pipes[i]);
		i++;
	}
}

static int	create_pipes(int *pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pipe(pipes + i * 2) == -1)
		{
			while (i > 0)
			{
				i--;
				close(pipes[i * 2]);
				close(pipes[i * 2 + 1]);
			}
			return (-1);
		}
		i++;
	}
	return (0);
}

static void	setup_pipe_child(int *pipes, int index, int count)
{
	if (index > 0)
		dup2(pipes[(index - 1) * 2], STDIN_FILENO);
	if (index < count - 1)
		dup2(pipes[index * 2 + 1], STDOUT_FILENO);
	close_pipes(pipes, count - 1);
}

static void	wait_all_children(pid_t *pids, int count)
{
	int	i;
	int	status;

	i = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		if (i == count - 1)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
}

int	execute_pipes(t_cmd *cmds, char ***env)
{
	(void)cmds;
	(void)env;
	// TODO: Implémenter la logique complète des pipes
	// Utiliser create_pipes, setup_pipe_child, wait_all_children
	return (0);
}
