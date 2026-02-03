/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 14:55:00 by mehdi             #+#    #+#             */
/*   Updated: 2026/01/11 15:00:00 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token_type(char *str, int i)
{
	if (str[i] == '|')
		return (PIPE);
	if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	if (str[i] == '<')
		return (REDIR_IN);
	if (str[i] == '>' && str[i + 1] == '>')
		return (REDIR_APPEND);
	if (str[i] == '>')
		return (REDIR_OUT);
	return (WORD);
}

t_token	*create_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token_back(t_token **tokens, t_token *new_token)
{
	t_token	*tmp;

	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
}

int	process_token(char *input, int *i, t_token **tokens)
{
	int		len;
	char	*value;
	t_token	*token;

	if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
		return (process_operator(input, i, tokens));
	len = get_word_len(input, *i);
	value = extract_word(input, *i, len);
	if (!value)
		return (0);
	token = create_token(value, WORD);
	if (!token)
	{
		free(value);
		return (0);
	}
	add_token_back(tokens, token);
	*i += len;
	return (1);
}
