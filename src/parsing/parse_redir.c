/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanisubu <yanisubu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/01/15 10:00:00 by yanisubu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_redir(t_cmd *cmd, t_token *token)
{
	if (!token->next || token->next->type != WORD)
		return (0);
	if (token->type == REDIR_IN)
	{
		free(cmd->infile);
		cmd->infile = ft_strdup(token->next->value);
	}
	else if (token->type == REDIR_OUT)
	{
		free(cmd->outfile);
		cmd->outfile = ft_strdup(token->next->value);
		cmd->append = 0;
	}
	else if (token->type == REDIR_APPEND)
	{
		free(cmd->outfile);
		cmd->outfile = ft_strdup(token->next->value);
		cmd->append = 1;
	}
	else if (token->type == HEREDOC)
	{
		free(cmd->heredoc);
		cmd->heredoc = ft_strdup(token->next->value);
	}
	return (1);
}

int	process_redirections(t_cmd *cmd, t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type >= REDIR_IN && tmp->type <= HEREDOC)
		{
			if (!handle_redir(cmd, tmp))
				return (0);
			tmp = tmp->next;
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (1);
}

// j'ai du ajouter ce fichier sinon ça marchait pas j'ai pas encore regardé pourquoi