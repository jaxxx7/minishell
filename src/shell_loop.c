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

static void	process_input(char *input, char ***env)
{
	t_token	*tokens;
	t_cmd	*cmds;

	add_history(input);
	tokens = tokenize(input);
	free(input);
	if (!tokens)
		return ;
	tokens = expand_tokens(tokens, *env);
	if (!tokens)
		return ;
	cmds = parse_commands(tokens);
	free_tokens(tokens);
	if (!cmds)
		return ;
	execute_commands(cmds, env);
	free_commands(cmds);
}

void	shell_loop(char **env)
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
		process_input(input, &env);
	}
}
