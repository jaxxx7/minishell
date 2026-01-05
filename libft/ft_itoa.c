/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:20:18 by mhachem           #+#    #+#             */
/*   Updated: 2025/04/30 16:38:02 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	size_count(int n)
{
	int	total;

	total = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		total++;
	}
	return (total);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*result;
	int		is_negative;
	long	nb;

	nb = (long)n;
	is_negative = (nb < 0);
	if (is_negative)
		nb = -nb;
	size = size_count(nb) + is_negative;
	result = malloc(sizeof(char) * size + 1);
	if (!result)
		return (0);
	result[size] = '\0';
	if (is_negative)
		result[0] = '-';
	while (size > is_negative)
	{
		result[size - 1] = ((nb % 10) + '0');
		nb /= 10;
		size--;
	}
	return (result);
}
/*
int main()
{
	char *test = ft_itoa(-2147483648);
	printf("result : %s", test);
}
*/