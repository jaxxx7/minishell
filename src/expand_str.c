/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 17:00:00 by mehdi             #+#    #+#             */
/*   Updated: 2026/01/11 17:10:00 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_var_found(char *str, int *i, char **env, char *result)
{
	int		len;
	char	*chunk;
	char	*var_val;

	len = get_var_len(&str[*i + 1]);
	chunk = ft_substr(str, *i + 1, len);
	if (!chunk)
		return (free(result), NULL);
	var_val = get_env_value(chunk, env);
	free(chunk);
	result = strjoin_free_s1(result, var_val);
	if (!result)
		return (NULL);
	*i += 1 + len;
	return (result);
}

static char	*expand_dollar_only(char *str, int *i, char *result)
{
	char	*chunk;

	chunk = ft_substr(str, *i, 1);
	if (!chunk)
		return (free(result), NULL);
	result = strjoin_free_s1(result, chunk);
	free(chunk);
	if (!result)
		return (NULL);
	(*i)++;
	return (result);
}

static char	*expand_variable(char *str, int *i, char **env, char *result)
{
	int		len;

	len = get_var_len(&str[*i + 1]);
	if (len > 0)
		return (expand_var_found(str, i, env, result));
	else
		return (expand_dollar_only(str, i, result));
}

static char	*expand_text(char *str, int *i, char *result)
{
	int		start;
	char	*chunk;

	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	chunk = ft_substr(str, start, *i - start);
	if (!chunk)
		return (free(result), NULL);
	result = strjoin_free_s1(result, chunk);
	free(chunk);
	if (!result)
		return (NULL);
	return (result);
}

char	*expand_str(char *str, char **env)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			result = expand_variable(str, &i, env, result);
			if (!result)
				return (NULL);
		}
		else
		{
			result = expand_text(str, &i, result);
			if (!result)
				return (NULL);
		}
	}
	return (result);
}
