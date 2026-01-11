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
int g_exit_status = 0;

// Gestion du signal Ctrl+C (SIGINT)
void handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 130;
}

// Initialisation des signaux
void setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

// Affiche les tokens (debug)
void print_tokens(t_token *tokens)
{
	t_token *tmp;
	char *type_str;

	tmp = tokens;
	printf("\n=== TOKENS ===\n");
	while (tmp)
	{
		if (tmp->type == WORD)
			type_str = "WORD";
		else if (tmp->type == PIPE)
			type_str = "PIPE";
		else if (tmp->type == REDIR_IN)
			type_str = "REDIR_IN";
		else if (tmp->type == REDIR_OUT)
			type_str = "REDIR_OUT";
		else if (tmp->type == REDIR_APPEND)
			type_str = "REDIR_APPEND";
		else if (tmp->type == HEREDOC)
			type_str = "HEREDOC";
		else
			type_str = "UNKNOWN";
		printf("[%s: \"%s\"]\n", type_str, tmp->value);
		tmp = tmp->next;
	}
	printf("==============\n\n");
}

// Affiche une commande (debug)
void print_single_cmd(t_cmd *cmd, int cmd_num)
{
	int i;

	printf("--- Commande %d ---\n", cmd_num);
	if (cmd->args)
	{
		printf("Args: ");
		i = 0;
		while (cmd->args[i])
		{
			printf("\"%s\"", cmd->args[i]);
			if (cmd->args[i + 1])
				printf(", ");
			i++;
		}
		printf("\n");
	}
	if (cmd->infile)
		printf("Input: < %s\n", cmd->infile);
	if (cmd->outfile)
		printf("Output: %s %s\n", cmd->append ? ">>" : ">", cmd->outfile);
	if (cmd->heredoc)
		printf("Heredoc: << %s\n", cmd->heredoc);
}

// Affiche toutes les commandes (debug)
void print_commands(t_cmd *cmds)
{
	t_cmd *tmp;
	int i;

	tmp = cmds;
	i = 1;
	printf("\n=== COMMANDES ===\n");
	while (tmp)
	{
		print_single_cmd(tmp, i);
		tmp = tmp->next;
		i++;
	}
	printf("=================\n\n");
}

// Boucle principale (version debug)
void shell_loop(char **env)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;

	while (1)
	{
		input = readline("minishell> ");
		
		// Gestion de EOF (Ctrl+D)
		if (!input)
		{
			write(1, "exit\n", 5);
			break;
		}
		
		// Ignore les lignes vides
		if (!*input)
		{
			free(input);
			continue;
		}
		
		add_history(input);
		
		// ÉTAPE 1: Tokenization
		tokens = tokenize(input);
		free(input);
		
		if (!tokens)
		{
			ft_putendl_fd("minishell: tokenization error", 2);
			continue;
		}
		
		// DEBUG: Affiche les tokens
		print_tokens(tokens);
		
		// ÉTAPE 2: Expansion
		tokens = expand_tokens(tokens, env);
		if (!tokens)
		{
			ft_putendl_fd("minishell: expansion error", 2);
			continue;
		}
		
		// ÉTAPE 3: Parsing
		cmds = parse_commands(tokens);
		free_tokens(tokens);
		
		if (!cmds)
			continue;
		
		// DEBUG: Affiche les commandes parsées
		print_commands(cmds);
		
		// ÉTAPE 4: Exécution (NON IMPLÉMENTÉE)
		printf("⚠️  Exécution non implémentée pour le moment\n\n");
		
		// Cleanup
		free_commands(cmds);
	}
}

// Copie de l'environnement
char **copy_env(char **envp)
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
void free_env(char **env)
{
	int i;

	if (!env)
		return;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

int main(int ac, char **av, char **envp)
{
	char **env;

	(void)ac;
	(void)av;
	
	printf("\n╔════════════════════════════════════════╗\n");
	printf("║     MINISHELL - MODE DEBUG PARSING     ║\n");
	printf("╚════════════════════════════════════════╝\n\n");
	printf("✅ Tokenization implémentée\n");
	printf("✅ Expansion implémentée\n");
	printf("✅ Parsing implémenté\n");
	printf("⚠️  Exécution NON implémentée\n\n");
	printf("Commandes de test:\n");
	printf("  • echo hello world\n");
	printf("  • ls -la | grep test\n");
	printf("  • cat < infile > outfile\n");
	printf("  • echo test >> file.txt\n");
	printf("  • cat << EOF\n\n");
	
	// Copie de l'environnement
	env = copy_env(envp);
	if (!env)
	{
		ft_putendl_fd("minishell: fatal: cannot copy environment", 2);
		return (1);
	}
	
	// Configuration des signaux
	setup_signals();
	
	// Boucle principale
	shell_loop(env);
	
	// Cleanup
	free_env(env);
	clear_history();
	
	return (g_exit_status);
}
