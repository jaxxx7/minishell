/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:40:00 by mehdi             #+#    #+#             */
/*   Updated: 2026/01/11 16:24:50 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

/* ************************************************************************** */
/*                              ENUMS & DEFINES                               */
/* ************************************************************************** */

# define WORD 0
# define PIPE 1
# define REDIR_IN 2
# define REDIR_OUT 3
# define REDIR_APPEND 4
# define HEREDOC 5

/* ************************************************************************** */
/*                               STRUCTURES                                   */
/* ************************************************************************** */

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	int				append;
	char			*heredoc;
	struct s_cmd	*next;
}	t_cmd;

/* ************************************************************************** */
/*                           GLOBAL VARIABLE                                  */
/* ************************************************************************** */

extern int	g_exit_status;

/* ************************************************************************** */
/*                           TOKENIZATION                                     */
/* ************************************************************************** */

// tokenize.c
t_token	*tokenize(char *input);
int		process_token(char *input, int *i, t_token **tokens);

// tokenize_word.c
int		get_word_len(char *str, int start);
char	*extract_word(char *str, int start, int len);

// tokenize_free.c
void	free_tokens(t_token *tokens);

/* ************************************************************************** */
/*                              PARSING                                       */
/* ************************************************************************** */

// parse_commands.c
t_cmd	*parse_commands(t_token *tokens);

// parse_single_cmd.c
t_cmd	*parse_single_cmd(t_token *tokens);

// parse_syntax.c
int		check_syntax(t_token *tokens);

// parse_free.c
void	free_single_cmd(t_cmd *cmd);
void	free_commands(t_cmd *cmds);

/* ************************************************************************** */
/*                              EXPANSION                                     */
/* ************************************************************************** */

// expand_tokens.c
t_token	*expand_tokens(t_token *tokens, char **env);

// expand_utils.c
char	*get_env_value(char *var_name, char **env);
int		get_var_len(char *str);
char	*strjoin_free_s1(char *s1, char *s2);

// expand_str.c
char	*expand_str(char *str, char **env);

/* ************************************************************************** */
/*                              EXECUTION                                     */
/* ************************************************************************** */

// execute.c (À IMPLÉMENTER)
void	execute_commands(t_cmd *cmds, char ***env);

/* ************************************************************************** */
/*                              BUILTINS                                      */
/* ************************************************************************** */

// builtins (À IMPLÉMENTER)
int		builtin_echo(char **args);
int		builtin_cd(char **args, char ***env);
int		builtin_pwd(void);
int		builtin_export(char **args, char ***env);
int		builtin_unset(char **args, char ***env);
int		builtin_env(char **env);
int		builtin_exit(char **args);

/* ************************************************************************** */
/*                           ENVIRONMENT                                      */
/* ************************************************************************** */

// env_utils.c (À IMPLÉMENTER)
char	**copy_env(char **envp);
void	free_env(char **env);

#endif