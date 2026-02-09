/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:00:00 by mehdi             #+#    #+#             */
/*   Updated: 2026/01/11 17:04:11 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Variable globale pour l'exit status
int	g_exit_status = 0;

// Gestion du signal Ctrl+C (SIGINT)
void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}

// Initialisation des signaux
void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

// Copie de l'environnement
char	**copy_env(char **envp)
{
	char	**env_copy;
	int		i;
	int		count;

	count = 0;
	while (envp[count])
		count++;
	env_copy = malloc(sizeof(char *) * (count + 1));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		env_copy[i] = ft_strdup(envp[i]);
		if (!env_copy[i])
		{
			while (i > 0)
				free(env_copy[--i]);
			free(env_copy);
			return (NULL);
		}
		i++;
	}
	env_copy[count] = NULL;
	return (env_copy);
}

// Libération de l'environnement
void	free_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
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
	clear_history();
	return (g_exit_status);
}
