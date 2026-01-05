/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:19:44 by mhachem           #+#    #+#             */
/*   Updated: 2025/04/30 11:19:47 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	*ft_calloc( size_t elementCount, size_t elementSize)
{
	char	*result;

	result = malloc(elementSize * elementCount);
	if (!result)
		return (0);
	ft_memset(result, 0, elementCount * elementSize);
	return (result);
}
