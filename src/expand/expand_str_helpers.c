/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 17:10:00 by mehdi             #+#    #+#             */
/*   Updated: 2026/02/22 17:13:31 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_append_char(char *result, char c)
{
	char	chunk[2];

	chunk[0] = c;
	chunk[1] = '\0';
	result = strjoin_free_s1(result, chunk);
	if (!result)
		return (NULL);
	return (result);
}

char	*expand_handle_backslash(char *str, int *i, char *result)
{
	if (str[*i + 1] && (str[*i + 1] == '$' || str[*i + 1] == '\\'))
	{
		result = expand_append_char(result, str[*i + 1]);
		if (!result)
			return (NULL);
		*i += 2;
		return (result);
	}
	result = expand_append_char(result, str[*i]);
	if (!result)
		return (NULL);
	(*i)++;
	return (result);
}

char	*expand_text_chunk(char *str, int *i, char *result)
{
	int		start;
	char	*chunk;

	start = *i;
	while (str[*i] && str[*i] != '$' && str[*i] != '\\')
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
