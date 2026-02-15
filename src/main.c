/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:00:00 by mehdi             #+#    #+#             */
/*   Updated: 2026/02/15 15:07:46 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

// Gestion du signal Ctrl+C (SIGINT)
void	handle_sigint(int sig)
{
	g_signal = sig;
	write(1, "^C\n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// Initialisation des signaux
void	setup_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **envp)
{
	char	**env;

	(void)ac;
	(void)av;
	env = copy_env(envp);
	if (!env)
	{
		ft_putendl_fd("minishell: fatal: cannot copy environment", 2);
		return (1);
	}
	setup_signals();
	shell_loop(&env);
	free_env(env);
	rl_clear_history();
	return (get_exit_status());
}
