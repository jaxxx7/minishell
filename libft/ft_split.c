/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:53:15 by mhachem           #+#    #+#             */
/*   Updated: 2025/05/12 13:02:45 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	is_charset(char const *s, char c)
{
	if (*s == c)
		return (1);
	return (0);
}

int	words_count(char const *s, char c)
{
	int	word;
	int	i;
	int	count;

	word = 0;
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && word == 0)
		{
			count++;
			word = 1;
		}
		if (s[i] == c)
			word = 0;
		i++;
	}
	return (count);
}

static int	fill_word(char **res, const char *s, int i, char c)
{
	int	k;

	k = 0;
	while (s[i + k] && s[i + k] != c)
		k++;
	res[0] = malloc(k + 1);
	if (!res[0])
		return (0);
	ft_strlcpy(res[0], &s[i], k + 1);
	return (k);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		len;
	char	**result;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	result = malloc(sizeof(char *) * (words_count(s, c) + 1));
	if (!result)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
		{
			len = fill_word(&result[j], s, i, c);
			i += len;
			j++;
		}
		else
			i++;
	}
	result[j] = NULL;
	return (result);
}
