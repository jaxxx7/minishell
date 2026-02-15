/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/02/15 15:31:30 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_heredoc_line(int fd, char *line, char **env)
{
	char	*expanded;

	if (!ft_strchr(line, '$'))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		return (0);
	}
	expanded = expand_str(line, env);
	if (!expanded)
		return (-1);
	write(fd, expanded, ft_strlen(expanded));
	write(fd, "\n", 1);
	free(expanded);
	return (0);
}

static int	hd_input(char *line, char *delimiter, int fd, char **env)
{
	if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
	{
		free(line);
		return (1);
	}
	if (write_heredoc_line(fd, line, env) == -1)
	{
		free(line);
		return (-1);
	}
	free(line);
	return (0);
}

static int	read_heredoc_lines(int fd, char *delimiter, char **env)
{
	char	*line;
	int		status;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_signal == SIGINT)
			{
				set_exit_status(130);
				g_signal = 0;
				return (-1);
			}
			print_error("warning", "here-document delimited by end-of-file");
			break ;
		}
		status = hd_input(line, delimiter, fd, env);
		if (status == 1)
			break ;
		if (status == -1)
			return (-1);
	}
	return (0);
}

int	handle_heredoc(char *delimiter, char **env)
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
	if (read_heredoc_lines(pipe_fd[1], delimiter, env) == -1)
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

int	prepare_heredocs(t_cmd *cmds, char **env)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		if (current->heredoc)
		{
			current->heredoc_fd = handle_heredoc(current->heredoc, env);
			free(current->heredoc);
			current->heredoc = NULL;
			if (current->heredoc_fd == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
