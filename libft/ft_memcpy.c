/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:20:26 by mhachem           #+#    #+#             */
/*   Updated: 2025/05/12 12:53:25 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memcpy( void *destination, const void *source, size_t size)
{
	unsigned char	*new_dest;
	unsigned char	*src;
	size_t			i;

	i = 0;
	if (destination == source || size == 0)
		return (destination);
	new_dest = (unsigned char *)destination;
	src = (unsigned char *)source;
	while (i < size)
	{
		new_dest[i] = src[i];
		i++;
	}
	return (destination);
}
