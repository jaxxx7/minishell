/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanisubu <yanisubu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/01/15 10:00:00 by yanisubu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_commands(t_cmd *cmds)
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

static int	execute_single(t_cmd *cmd, char ***env)
{
	int	ret;

	if (cmd->redir_error)
	{
		g_exit_status = 1;
		return (0);
	}
	if (is_builtin(cmd->args[0]))
	{
		ret = execute_builtin(cmd, env);
		if (ret == -1)
			return (1);
		g_exit_status = ret;
		return (0);
	}
	g_exit_status = execute_external(cmd, *env);
	return (0);
}

static void	execute_pipeline(t_cmd *cmds, char ***env)
{
	execute_pipes(cmds, env);
}

int	execute_commands(t_cmd *cmds, char ***env)
{
	int	cmd_count;

	if (!cmds || !cmds->args || !cmds->args[0] || !cmds->args[0][0])
		return (0);
	cmd_count = count_commands(cmds);
	if (cmd_count == 1)
		return (execute_single(cmds, env));
	execute_pipeline(cmds, env);
	return (0);
}
