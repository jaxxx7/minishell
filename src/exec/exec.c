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

static void	execute_single(t_cmd *cmd, char ***env)
{
	if (is_builtin(cmd->args[0]))
		g_exit_status = execute_builtin(cmd, env);
	else
		g_exit_status = execute_external(cmd, *env);
}

static void	execute_pipeline(t_cmd *cmds, char ***env)
{
	execute_pipes(cmds, env);
}

void	execute_commands(t_cmd *cmds, char ***env)
{
	int	cmd_count;

	if (!cmds || !cmds->args || !cmds->args[0])
		return ;
	cmd_count = count_commands(cmds);
	if (cmd_count == 1)
		execute_single(cmds, env);
	else
		execute_pipeline(cmds, env);
}
