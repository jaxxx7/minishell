/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:00:00 by mehdi             #+#    #+#             */
/*   Updated: 2026/01/11 17:04:11 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (process_input(input, env))
			break ;
	}
}
