/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/02/15 14:10:32 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <fcntl.h>

static void	set_redir_error(t_cmd *cmd, char *file, char *msg)
{
	if (cmd->redir_error)
		return ;
	cmd->redir_error = 1;
	cmd->redir_err_file = ft_strdup(file);
	cmd->redir_err_msg = ft_strdup(msg);
}

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
		set_redir_error(cmd, token->next->value, "Permission denied");
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
		set_redir_error(cmd, filename, "No such file or directory");
		return ;
	}
	free(cmd->infile);
	cmd->infile = ft_strdup(filename);
	cmd->input_type = REDIR_IN;
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
		cmd->input_type = HEREDOC;
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
