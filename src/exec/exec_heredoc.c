/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanisubu <yanisubu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/01/15 10:00:00 by yanisubu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_to_pipe(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	return (0);
}

static int	read_heredoc_lines(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_exit_status == 130)
			{
				return (-1);
			}
			print_error("warning", "here-document delimited by end-of-file");
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		write_to_pipe(fd, line);
		free(line);
	}
	return (0);
}

int	handle_heredoc(char *delimiter)
{
	int	pipe_fd[2];
	int	stdin_copy;

	if (pipe(pipe_fd) == -1)
	{
		print_error("pipe", "failed to create heredoc pipe");
		return (-1);
	}
	stdin_copy = dup(STDIN_FILENO);
	signal(SIGINT, herydoc_sigint);
	if (read_heredoc_lines(pipe_fd[1], delimiter) == -1)
	{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		dup2(stdin_copy, STDIN_FILENO);
		close(stdin_copy);
		signal(SIGINT, handle_sigint);
		return (-1);
	}
	close(stdin_copy);
	signal(SIGINT, handle_sigint);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

void	drain_heredoc(char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		free(line);
	}
}

int	prepare_heredocs(t_cmd *cmds)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		if (current->heredoc)
		{
			current->heredoc_fd = handle_heredoc(current->heredoc);
			free(current->heredoc);
			current->heredoc = NULL;
			if (current->heredoc_fd == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
