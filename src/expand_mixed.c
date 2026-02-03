/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_mixed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanisubu <yanisubu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/02/03 10:00:00 by yanisubu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_char(char *result, char c)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	return (strjoin_free_s1(result, str));
}

static char	*handle_single_quote(char *str, int *i, char *result)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		result = add_char(result, str[*i]);
		if (!result)
			return (NULL);
		(*i)++;
	}
	if (str[*i] == '\'')
		(*i)++;
	return (result);
}

static char	*handle_double_quote(char *str, int *i, char *result, char **env)
{
	int		start;
	char	*chunk;
	char	*expanded;

	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != '"')
		(*i)++;
	chunk = ft_substr(str, start, *i - start);
	if (!chunk)
		return (free(result), NULL);
	expanded = expand_str(chunk, env);
	free(chunk);
	if (!expanded)
		return (free(result), NULL);
	result = strjoin_free_s1(result, expanded);
	free(expanded);
	if (str[*i] == '"')
		(*i)++;
	return (result);
}

static char	*handle_unquoted(char *str, int *i, char *result, char **env)
{
	int		start;
	char	*chunk;
	char	*expanded;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"')
		(*i)++;
	chunk = ft_substr(str, start, *i - start);
	if (!chunk)
		return (free(result), NULL);
	expanded = expand_str(chunk, env);
	free(chunk);
	if (!expanded)
		return (free(result), NULL);
	result = strjoin_free_s1(result, expanded);
	free(expanded);
	return (result);
}

char	*expand_mixed(char *str, char **env)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i] && result)
	{
		if (str[i] == '\'')
			result = handle_single_quote(str, &i, result);
		else if (str[i] == '"')
			result = handle_double_quote(str, &i, result, env);
		else
			result = handle_unquoted(str, &i, result, env);
	}
	return (result);
}
