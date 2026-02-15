/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:00:00 by mehdi             #+#    #+#             */
/*   Updated: 2026/02/15 13:54:45 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_unclosed_quotes(char *input)
{
	int	single_q;
	int	double_q;
	int	i;

	single_q = 0;
	double_q = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !double_q)
			single_q = !single_q;
		else if (input[i] == '"' && !single_q)
			double_q = !double_q;
		i++;
	}
	return (single_q || double_q);
}

static int	process_input(char *input, char ***env)
{
	t_token	*tokens;
	t_cmd	*cmds;
	int		should_exit;

	add_history(input);
	tokens = tokenize(input);
	free(input);
	if (!tokens)
		return (0);
	tokens = expand_tokens(tokens, *env);
	if (!tokens)
		return (0);
	cmds = parse_commands(tokens);
	free_tokens(tokens);
	if (!cmds)
		return (0);
	if (prepare_heredocs(cmds) == -1)
	{
		free_commands(cmds);
		return (0);
	}
	should_exit = execute_commands(cmds, env);
	free_commands(cmds);
	return (should_exit);
}

void	shell_loop(char ***env)
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (!*input)
		{
			free(input);
			continue ;
		}
		if (has_unclosed_quotes(input))
		{
			ft_putendl_fd("syntax error: unclosed quote", 2);
			g_exit_status = 2;
			free(input);
			continue ;
		}
		if (process_input(input, env))
			break ;
	}
}
