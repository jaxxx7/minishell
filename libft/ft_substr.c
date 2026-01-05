/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:22:50 by mhachem           #+#    #+#             */
/*   Updated: 2025/04/30 16:30:32 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*result;
	size_t			i;
	size_t			real_len;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	real_len = ft_strlen(s + start);
	if (real_len > len)
		real_len = len;
	result = malloc(sizeof(char) * real_len + 1);
	if (!result)
		return (0);
	i = 0;
	while (i < real_len && s[start])
	{
		result[i] = s[start];
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}
/*
int main()
{
	char *s = "salut tout le monde";
	int start = 1;
	size_t len = 2;
	printf("%s", ft_substr(s, start, len));
}
*/