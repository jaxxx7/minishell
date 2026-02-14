/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanisubu <yanisubu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/01/15 10:00:00 by yanisubu         ###   ########.fr       */
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

int	setup_redirections(t_cmd *cmd)
{
	if (cmd->heredoc)
	{
		int fd = handle_heredoc(cmd->heredoc);
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			print_error("dup2", "failed");
			return (-1);
		}
		close(fd);
	}
	else if (cmd->infile)
	{
		if (setup_input_redir(cmd->infile) == -1)
			return (-1);
	}
	if (cmd->outfile)
	{
		if (setup_output_redir(cmd->outfile, cmd->append) == -1)
			return (-1);
	}
	return (0);
}
