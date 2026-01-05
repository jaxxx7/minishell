/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 13:45:35 by mhachem           #+#    #+#             */
/*   Updated: 2026/01/05 14:27:59 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd   *parse_input(char *input, char **env)
{
    t_token *tokens;
    t_cmd   *commands;

    // 1. Lexing : String -> Liste de tokens
    tokens = lexer(input);
    if (!tokens)
        return (NULL);
    // 2. Expansion : $VAR -> valeur
    expand_tokens(tokens, env);
    // 3. Quote Removal : "mot" -> mot
   remove_quotes(tokens);
    // 4. Parsing : Tokens -> Commandes structurées
    commands = create_commands(tokens);
    // Nettoyage de la liste temporaire de tokens (si besoin)
    free_tokens(tokens);

    return (commands);
}