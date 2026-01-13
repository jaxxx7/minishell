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
	int		quote_type;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			quote_type = get_quote_type(tmp->value);
			if (quote_type == 1 && !expand_single_quote(tmp))
				return (NULL);
			else if (quote_type == 2 && !expand_double_quote(tmp, env))
				return (NULL);
			else if (quote_type == 0 && !expand_no_quote(tmp, env))
				return (NULL);
		}
		tmp = tmp->next;
	}
	return (tokens);
}
