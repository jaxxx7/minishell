/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanisubu <yanisubu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/02/21 10:00:00 by yanisubu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	get_stripped_len(const char *s)
{
	int	i;
	int	len;

	if (!s)
		return (0);
	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '\\' && s[i + 1])
		{
			len++;
			i += 2;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*fill_stripped(const char *s, int len)
{
	int		i;
	int		j;
	char	*out;

	out = malloc(len + 1);
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\\' && s[i + 1])
			i++;
		out[j++] = s[i++];
	}
	out[j] = '\0';
	return (out);
}
