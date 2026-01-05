/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 12:42:17 by mhachem           #+#    #+#             */
/*   Updated: 2026/01/05 16:38:54 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"

// Les types de tokens (pour ton usage interne au parsing)
typedef enum e_token_type {
    WORD,       // Un mot classique (ls, -l, fichier.txt)
    PIPE,       // |
    REDIR_IN,   // <
    REDIR_OUT,  // >
    APPEND,     // >>
    HEREDOC,    // <<
} t_type;

// Structure intermédiaire : Liste de tokens (mots bruts)
typedef struct s_token {
    char            *value; // Le texte (ex: "ls", "|", ">")
    t_type          type;   // Le type
    struct s_token  *next;
} t_token;

// --- CE QUE TU DONNES A TON MATE (L'EXEC) ---

// Structure finale : Une commande
typedef struct s_cmd {
    char            **args;    // Tableau pour execve : {"ls", "-l", NULL}
    // Tu peux gérer les redirections ici, ou via une liste séparée
    // Pour faire simple, une petite liste de redirections attachée à la commande :
    t_token         *redirections; // Liste des fichiers in/out pour cette commande
    struct s_cmd    *next;     // La prochaine commande après le pipe (ou NULL)
} t_cmd;

// /PARSING

// lexer.c
t_token *new_token(int type, char *str);
void	token_add_back(t_token **head, t_token *new_token);
t_token *lexer(char *input);

// utils.c
int     is_separator(char c);

#endif