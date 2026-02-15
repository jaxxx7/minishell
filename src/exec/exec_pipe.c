/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/02/15 15:04:49 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

void	close_pipes(int *pipes, int count)
{
	int	i;

	i = 0;
	while (i < (count - 1) * 2)
	{
		close(pipes[i]);
		i++;
	}
}

int	create_pipes(int *pipes, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
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

void	setup_pipe_child(int *pipes, int index, int count)
{
	if (index > 0)
		dup2(pipes[(index - 1) * 2], STDIN_FILENO);
	if (index < count - 1)
		dup2(pipes[index * 2 + 1], STDOUT_FILENO);
	close_pipes(pipes, count);
}

void	wait_all_children(pid_t *pids, int count)
{
	int	i;
	int	status;
	int	sig_printed;

	sig_printed = 0;
	i = -1;
	while (++i < count)
	{
		waitpid(pids[i], &status, 0);
		if (WIFSIGNALED(status) && !sig_printed)
		{
			if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
			else if (WTERMSIG(status) == SIGQUIT)
				ft_putendl_fd("Quit (core dumped)", 2);
			sig_printed = 1;
		}
		if (i == count - 1)
		{
			if (WIFEXITED(status))
				set_exit_status(WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				set_exit_status(128 + WTERMSIG(status));
		}
	}
}
