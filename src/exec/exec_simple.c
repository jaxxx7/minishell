/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanisubu <yanisubu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/01/15 10:00:00 by yanisubu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static void	child_process(t_cmd *cmd, char **env)
{
	char	*path;

	if (setup_redirections(cmd) == -1)
		exit(1);
	path = get_cmd_path(cmd->args[0], env);
	if (!path)
	{
		print_error(cmd->args[0], "command not found");
		exit(127);
	}
	execve(path, cmd->args, env);
	print_error(cmd->args[0], "execution failed");
	free(path);
	exit(126);
}

static int	wait_for_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	execute_external(t_cmd *cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		print_error("fork", "failed to create process");
		return (1);
	}
	if (pid == 0)
		child_process(cmd, env);
	return (wait_for_child(pid));
}
