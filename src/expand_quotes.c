/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:00:00 by mehdi             #+#    #+#             */
/*   Updated: 2026/01/11 18:10:00 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_quote_type(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		return (1);
	if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
		return (2);
	return (0);
}

char	*remove_quotes(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 2)
		return (ft_strdup(str));
	return (ft_substr(str, 1, len - 2));
}

int	expand_single_quote(t_token *tmp)
{
	char	*unquoted;

	unquoted = remove_quotes(tmp->value);
	if (!unquoted)
		return (0);
	free(tmp->value);
	tmp->value = unquoted;
	return (1);
}

int	expand_double_quote(t_token *tmp, char **env)
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

int	expand_no_quote(t_token *tmp, char **env)
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
