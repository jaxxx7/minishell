/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_single_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:15:00 by mehdi             #+#    #+#             */
/*   Updated: 2026/01/11 15:25:00 by mehdi            ###   ########.fr       */
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

static int	fill_args(t_cmd *cmd, t_token *tokens)
{
	int		i;
	int		count;

	count = count_args(tokens);
	cmd->args = malloc(sizeof(char *) * (count + 1));
	if (!cmd->args)
		return (0);
	i = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD)
			cmd->args[i++] = ft_strdup(tokens->value);
		else if (tokens->type >= REDIR_IN && tokens->type <= HEREDOC)
			tokens = tokens->next;
		if (tokens)
			tokens = tokens->next;
	}
	cmd->args[i] = NULL;
	return (1);
}

t_cmd	*parse_single_cmd(t_token *tokens)
{
	t_cmd	*cmd;

	cmd = init_cmd();
	if (!cmd)
		return (NULL);
	if (!process_redirections(cmd, tokens))
	{
		free_single_cmd(cmd);
		return (NULL);
	}
	if (!fill_args(cmd, tokens))
	{
		free_single_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}
