/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:28:30 by mehdi             #+#    #+#             */
/*   Updated: 2026/01/11 17:06:05 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_quote_type(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		return (1);
	if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
		return (2);
	return (0);
}

static char	*remove_quotes(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 2)
		return (ft_strdup(str));
	return (ft_substr(str, 1, len - 2));
}

static int	expand_single_quote(t_token *tmp)
{
	char	*unquoted;

	unquoted = remove_quotes(tmp->value);
	if (!unquoted)
		return (0);
	free(tmp->value);
	tmp->value = unquoted;
	return (1);
}

static int	expand_double_quote(t_token *tmp, char **env)
{
	char	*unquoted;
	char	*expanded_str;

	unquoted = remove_quotes(tmp->value);
	if (!unquoted)
		return (0);
	if (ft_strchr(unquoted, '$'))
	{
		expanded_str = expand_str(unquoted, env);
		free(unquoted);
		if (!expanded_str)
			return (0);
		free(tmp->value);
		tmp->value = expanded_str;
	}
	else
	{
		free(tmp->value);
		tmp->value = unquoted;
	}
	return (1);
}

static int	expand_no_quote(t_token *tmp, char **env)
{
	char	*expanded_str;

	if (ft_strchr(tmp->value, '$'))
	{
		expanded_str = expand_str(tmp->value, env);
		if (!expanded_str)
			return (0);
		free(tmp->value);
		tmp->value = expanded_str;
	}
	return (1);
}

t_token	*expand_tokens(t_token *tokens, char **env)
{
	t_token	*tmp;
	int		quote_type;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			quote_type = get_quote_type(tmp->value);
			if (quote_type == 1 && !expand_single_quote(tmp))
				return (NULL);
			else if (quote_type == 2 && !expand_double_quote(tmp, env))
				return (NULL);
			else if (quote_type == 0 && !expand_no_quote(tmp, env))
				return (NULL);
		}
		tmp = tmp->next;
	}
	return (tokens);
}
