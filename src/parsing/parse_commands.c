/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:10:00 by mehdi             #+#    #+#             */
/*   Updated: 2026/01/11 16:24:41 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = NULL;
	cmd->next = NULL;
	return (cmd);
}

static int	count_args(t_token *tokens)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			count++;
		else if (tmp->type >= REDIR_IN && tmp->type <= HEREDOC)
			tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
	}
	return (count);
}

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
			return (free_commands(cmds), NULL);
		current = current->next;
		pipe_pos = get_next_pipe(pipe_pos->next);
	}
	return (cmds);
}
