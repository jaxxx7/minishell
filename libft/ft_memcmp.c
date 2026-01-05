/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:20:22 by mhachem           #+#    #+#             */
/*   Updated: 2025/04/30 11:20:23 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_memcmp(const void *p1, const void *p2, size_t s)
{
	unsigned char	*mem1;
	unsigned char	*mem2;

	mem1 = (unsigned char *)p1;
	mem2 = (unsigned char *)p2;
	while (s--)
	{
		if (*mem1 != *mem2)
			return (*mem1 - *mem2);
		mem1++;
		mem2++;
	}
	return (0);
}
