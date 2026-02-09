/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:40:00 by mehdi             #+#    #+#             */
/*   Updated: 2026/01/13 12:43:23 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
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
	int				redir_error;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipe_data
{
	t_cmd	*cmds;
	char	***env;
	int		count;
}	t_pipe_data;

/* ************************************************************************** */
/*                           GLOBAL VARIABLE                                  */
/* ************************************************************************** */

extern int	g_exit_status;

/* ************************************************************************** */
/*                           TOKENIZATION                                     */
/* ************************************************************************** */

// tokenize.c
t_token	*tokenize(char *input);

// tokenize_word.c
int		get_word_len(char *str, int start);

// tokenize_word_utils.c
char	*extract_word(char *str, int start, int len);

// tokenize_utils.c
int		get_token_type(char *str, int i);
t_token	*create_token(char *value, int type);
void	add_token_back(t_token **tokens, t_token *new_token);
int		process_token(char *input, int *i, t_token **tokens);

// tokenize_operators.c
int		process_operator(char *input, int *i, t_token **tokens);

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
int		check_pipe(t_token *token);
int		check_redir(t_token *token);

// parse_redir.c
int		process_redirections(t_cmd *cmd, t_token *tokens);
int		handle_redir(t_cmd *cmd, t_token *token);

// parse_redir.c
int		process_redirections(t_cmd *cmd, t_token *tokens);

// parse_free.c
void	free_single_cmd(t_cmd *cmd);
void	free_commands(t_cmd *cmds);

/* ************************************************************************** */
/*                              EXPANSION                                     */
/* ************************************************************************** */

// expand_tokens.c
t_token	*expand_tokens(t_token *tokens, char **env);

// expand_quotes.c
int		get_quote_type(char *str);
char	*remove_quotes(char *str);
int		expand_single_quote(t_token *tmp);
int		expand_double_quote(t_token *tmp, char **env);
int		expand_no_quote(t_token *tmp, char **env);

// expand_utils.c
char	*get_env_value(char *var_name, char **env);
int		get_var_len(char *str);
char	*strjoin_free_s1(char *s1, char *s2);
char	*expand_exit_status(int *i, char *result);

// expand_str.c
char	*expand_str(char *str, char **env);

// expand_mixed.c
char	*expand_mixed(char *str, char **env);

/* ************************************************************************** */
/*                              EXECUTION                                     */
/* ************************************************************************** */

// exec.c
void	execute_commands(t_cmd *cmds, char ***env);

// exec_simple.c
int		execute_external(t_cmd *cmd, char **env);

// exec_path.c
char	*get_cmd_path(char *cmd, char **env);

// exec_redir.c
int		setup_redirections(t_cmd *cmd);

// exec_heredoc.c
int		handle_heredoc(char *delimiter);

// exec_pipe.c
int		execute_pipes(t_cmd *cmds, char ***env);
void	close_pipes(int *pipes, int count);
int		create_pipes(int *pipes, int count);
void	setup_pipe_child(int *pipes, int index, int count);
void	wait_all_children(pid_t *pids, int count);

// exec_pipe_utils.c
int		count_cmds(t_cmd *cmds);
t_cmd	*get_cmd_at(t_cmd *cmds, int index);
void	pipe_child_exec(t_cmd *cmd, char ***env);
int		*allocate_pipes(int count);
pid_t	*allocate_pids(int count);

// exec_error.c
void	print_error(char *cmd, char *msg);
void	print_error_arg(char *cmd, char *arg, char *msg);
void	print_exec_error(char *cmd, char *path);
int		error_return(char *cmd, char *msg, int ret);

// exec_signals.c
void	handle_sigint(int sig);
void	setup_child_signals(void);
void	setup_parent_signals(void);
void	restore_signals(void);

// exec_env.c
int		get_env_index(char *name, char **env);
char	*get_env_val(char *name, char **env);
int		set_env_var(char *name, char *value, char ***env);
int		add_env_var(char *new_var, char ***env);
int		unset_env_var(char *name, char ***env);

/* ************************************************************************** */
/*                              BUILTINS                                      */
/* ************************************************************************** */

// builtins.c
int		is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, char ***env);

// builtin_echo.c
int		builtin_echo(char **args);

// builtin_cd.c
int		builtin_cd(char **args, char ***env);

// builtin_pwd.c
int		builtin_pwd(void);

// builtin_export.c
int		builtin_export(char **args, char ***env);

// builtin_unset.c
int		builtin_unset(char **args, char ***env);

// builtin_env.c
int		builtin_env(char **env);

// builtin_exit.c
int		builtin_exit(char **args);

/* ************************************************************************** */
/*                           ENVIRONMENT                                      */
/* ************************************************************************** */

// env_utils.c
char	**copy_env(char **envp);
void	free_env(char **env);

// shell_loop.c
void	shell_loop(char **env);

#endif