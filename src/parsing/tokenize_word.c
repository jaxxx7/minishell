/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 14:22:41 by mehdi             #+#    #+#             */
/*   Updated: 2026/01/11 17:05:14 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ' ' || c == '\t');
}

static int	skip_quote(char *str, int i, char quote)
{
	i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}

int	get_word_len(char *str, int start)
{
	int		i;
	char	quote;

	i = start;
	while (str[i] && !is_special_char(str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			i = skip_quote(str, i, quote);
		}
		else
			i++;
	}
	return (i - start);
}

char	*extract_word(char *str, int start, int len)
{
	char	*word;

	word = ft_substr(str, start, len);
	if (!word)
		return (NULL);
	return (word);
}
