/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:20:00 by mehdi             #+#    #+#             */
/*   Updated: 2026/01/11 16:24:01 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(t_token *token)
{
	if (!token->next)
	{
		ft_putendl_fd("minishell: syntax error near `|'", 2);
		return (0);
	}
	if (token->next->type == PIPE)
	{
		ft_putendl_fd("minishell: syntax error near `|'", 2);
		return (0);
	}
	return (1);
}

int	check_redir(t_token *token)
{
	if (!token->next)
	{
		ft_putendl_fd("minishell: syntax error near redirection", 2);
		return (0);
	}
	if (token->next->type != WORD)
	{
		ft_putendl_fd("minishell: syntax error near redirection", 2);
		return (0);
	}
	return (1);
}

int	check_syntax(t_token *tokens)
{
	if (!tokens)
		return (0);
	if (tokens->type == PIPE)
	{
		ft_putendl_fd("minishell: syntax error near `|'", 2);
		return (0);
	}
	while (tokens)
	{
		if (tokens->type == PIPE && !check_pipe(tokens))
			return (0);
		if (tokens->type >= REDIR_IN && tokens->type <= HEREDOC)
		{
			if (!check_redir(tokens))
				return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}
