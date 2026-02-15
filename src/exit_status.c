/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:35:00 by mhachem           #+#    #+#             */
/*   Updated: 2026/02/15 15:07:46 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*exit_status_ptr(void)
{
	static int	exit_status;

	return (&exit_status);
}

int	get_exit_status(void)
{
	return (*exit_status_ptr());
}

void	set_exit_status(int status)
{
	*exit_status_ptr() = status;
}
