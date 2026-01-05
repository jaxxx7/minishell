/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:21:12 by mhachem           #+#    #+#             */
/*   Updated: 2025/04/30 15:51:28 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int searchedChar)
{
	while (*string)
	{
		if ((unsigned char)*string == (unsigned char)searchedChar)
			return ((char *)string);
		string++;
	}
	if ((unsigned char)*string == (unsigned char)searchedChar)
		return ((char *)string);
	return (0);
}
/*
int main()
{
	char *test = "salut tout le monde";
	char n = 'o';
	printf("%s", ft_strchr(test, n));
}
*/