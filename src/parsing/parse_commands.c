/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:10:00 by mehdi             #+#    #+#             */
/*   Updated: 2026/01/11 15:20:00 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*get_next_pipe(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
		tokens = tokens->next;
	return (tokens);
}

t_cmd	*parse_commands(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*current;
	t_token	*pipe_pos;

	if (!tokens || !check_syntax(tokens))
		return (NULL);
	cmds = parse_single_cmd(tokens);
	if (!cmds)
		return (NULL);
	current = cmds;
	pipe_pos = get_next_pipe(tokens);
	while (pipe_pos)
	{
		current->next = parse_single_cmd(pipe_pos->next);
		if (!current->next)
		{
			free_commands(cmds);
			return (NULL);
		}
		current = current->next;
		pipe_pos = get_next_pipe(pipe_pos->next);
	}
	return (cmds);
}
