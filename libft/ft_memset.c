/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:20:41 by mhachem           #+#    #+#             */
/*   Updated: 2025/04/30 11:20:42 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memset(void *pointer, int value, size_t count)
{
	unsigned char	*new_dest;
	unsigned char	src;
	size_t			i;

	i = 0;
	new_dest = (unsigned char *)pointer;
	src = (unsigned char)value;
	while (i < count)
	{
		new_dest[i] = src;
		i++;
	}
	return (pointer);
}
