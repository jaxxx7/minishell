/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/02/15 14:10:32 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static void	child_process(t_cmd *cmd, char **env)
{
	char	*path;

	if (setup_redirections(cmd) == -1)
		child_exit(cmd, env, 1);
	path = get_cmd_path(cmd->args[0], env);
	if (!path)
	{
		cmd_not_found(cmd->args[0]);
		child_exit(cmd, env, 127);
	}
	execve(path, cmd->args, env);
	print_exec_error(cmd->args[0], path);
	free(path);
	child_exit(cmd, env, 126);
}

static int	wait_for_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 2);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

int	execute_external(t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid == -1)
	{
		print_error("fork", "failed to create process");
		return (1);
	}
	if (pid == 0)
	{
		setup_child_signals();
		child_process(cmd, env);
	}
	setup_parent_signals();
	if (cmd->heredoc_fd != -1)
		close(cmd->heredoc_fd);
	ret = wait_for_child(pid);
	restore_signals();
	return (ret);
}
