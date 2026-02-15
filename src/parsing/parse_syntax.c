/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:20:00 by mehdi             #+#    #+#             */
/*   Updated: 2026/02/15 15:08:11 by mhachem          ###   ########.fr       */
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
		ft_putstr_fd("minishell: syntax error near `", 2);
		ft_putstr_fd(token->value, 2);
		ft_putendl_fd("'", 2);
		return (0);
	}
	if (token->next->type != WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(token->next->value, 2);
		ft_putendl_fd("'", 2);
		return (0);
	}
	return (1);
}

static int	syntax_error_ret(void)
{
	set_exit_status(2);
	return (0);
}

static int	check_token_syntax(t_token *tokens)
{
	if (tokens->type == PIPE && !check_pipe(tokens))
		return (syntax_error_ret());
	if (tokens->type >= REDIR_IN && tokens->type <= HEREDOC)
	{
		if (!check_redir(tokens))
			return (syntax_error_ret());
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
		return (syntax_error_ret());
	}
	while (tokens)
	{
		if (!check_token_syntax(tokens))
			return (0);
		tokens = tokens->next;
	}
	return (1);
}
