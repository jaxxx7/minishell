/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/02/03 13:38:10 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>

static void	handle_output_redir(t_cmd *cmd, t_token *token, int append)
{
	int	fd;
	int	flags;

	if (cmd->redir_error)
		return ;
	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(token->next->value, flags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token->next->value, 2);
		ft_putendl_fd(": Permission denied", 2);
		cmd->redir_error = 1;
		return ;
	}
	close(fd);
	free(cmd->outfile);
	cmd->outfile = ft_strdup(token->next->value);
	cmd->append = append;
}

static void	handle_input_redir(t_cmd *cmd, char *filename)
{
	if (cmd->redir_error)
		return ;
	if (access(filename, F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putendl_fd(": No such file or directory", 2);
		cmd->redir_error = 1;
		return ;
	}
	free(cmd->infile);
	cmd->infile = ft_strdup(filename);
}

int	handle_redir(t_cmd *cmd, t_token *token)
{
	if (!token->next || token->next->type != WORD)
		return (0);
	if (token->type == REDIR_IN)
		handle_input_redir(cmd, token->next->value);
	else if (token->type == REDIR_OUT)
		handle_output_redir(cmd, token, 0);
	else if (token->type == REDIR_APPEND)
		handle_output_redir(cmd, token, 1);
	else if (token->type == HEREDOC)
	{
		if (cmd->heredoc)
			drain_heredoc(cmd->heredoc);
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
