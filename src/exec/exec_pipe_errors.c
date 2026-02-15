/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:35:00 by mhachem           #+#    #+#             */
/*   Updated: 2026/02/15 15:07:46 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pipeline_redir_errors(t_cmd *cmds)
{
	while (cmds)
	{
		if (cmds->redir_error && cmds->redir_err_file && cmds->redir_err_msg)
			print_error(cmds->redir_err_file, cmds->redir_err_msg);
		cmds = cmds->next;
	}
}
