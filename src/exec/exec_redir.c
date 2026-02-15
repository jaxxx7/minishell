/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/02/15 15:08:11 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static int	setup_input_redir(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		print_error(infile, "No such file or directory");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		print_error("dup2", "failed");
		return (-1);
	}
	close(fd);
	return (0);
}

static int	setup_output_redir(char *outfile, int append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(outfile, flags, 0644);
	if (fd == -1)
	{
		print_error(outfile, "Permission denied");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		print_error("dup2", "failed");
		return (-1);
	}
	close(fd);
	return (0);
}

static int	setup_input_choice(t_cmd *cmd)
{
	if (cmd->input_type == HEREDOC && cmd->heredoc_fd != -1)
	{
		if (dup2(cmd->heredoc_fd, STDIN_FILENO) == -1)
		{
			close(cmd->heredoc_fd);
			print_error("dup2", "failed");
			return (-1);
		}
		close(cmd->heredoc_fd);
	}
	else if (cmd->input_type == REDIR_IN && cmd->infile
		&& setup_input_redir(cmd->infile) == -1)
		return (-1);
	return (0);
}

static void	close_unused_heredoc(t_cmd *cmd)
{
	if (cmd->input_type != HEREDOC && cmd->heredoc_fd != -1)
	{
		close(cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
}

int	setup_redirections(t_cmd *cmd)
{
	if (cmd->redir_error)
	{
		print_error(cmd->redir_err_file, cmd->redir_err_msg);
		return (-1);
	}
	if (setup_input_choice(cmd) == -1)
		return (-1);
	close_unused_heredoc(cmd);
	if (cmd->outfile && setup_output_redir(cmd->outfile, cmd->append) == -1)
		return (-1);
	return (0);
}
