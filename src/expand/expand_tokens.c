/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:28:30 by mehdi             #+#    #+#             */
/*   Updated: 2026/01/11 17:00:00 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*expand_tokens(t_token *tokens, char **env)
{
	t_token	*tmp;
	int		qt;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			qt = get_quote_type(tmp->value);
			if (qt == 1 && !expand_single_quote(tmp))
				return (NULL);
			else if (qt == 2 && !expand_double_quote(tmp, env))
				return (NULL);
			else if (qt == 0 && !expand_no_quote(tmp, env))
				return (NULL);
			if (!qt && !tmp->value[0])
				tmp->type = -1;
		}
		tmp = tmp->next;
	}
	return (tokens);
}
