/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 17:15:00 by mehdi             #+#    #+#             */
/*   Updated: 2026/01/11 17:20:00 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_redirections(t_cmd *cmd, t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type >= REDIR_IN && tokens->type <= HEREDOC)
		{
			if (!handle_redir(cmd, tokens))
				return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

int	handle_redir(t_cmd *cmd, t_token *token)
{
	if (!token->next || token->next->type != WORD)
		return (0);
	if (token->type == REDIR_IN)
		cmd->infile = ft_strdup(token->next->value);
	else if (token->type == REDIR_OUT)
	{
		cmd->outfile = ft_strdup(token->next->value);
		cmd->append = 0;
	}
	else if (token->type == REDIR_APPEND)
	{
		cmd->outfile = ft_strdup(token->next->value);
		cmd->append = 1;
	}
	else if (token->type == HEREDOC)
		cmd->heredoc = ft_strdup(token->next->value);
	return (1);
}
