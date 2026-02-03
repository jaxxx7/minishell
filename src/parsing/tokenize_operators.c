/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_operators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:15:00 by mehdi             #+#    #+#             */
/*   Updated: 2026/01/11 18:20:00 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_operator_len(char *str, int i)
{
	if ((str[i] == '<' && str[i + 1] == '<')
		|| (str[i] == '>' && str[i + 1] == '>'))
		return (2);
	if (str[i] == '<' || str[i] == '>' || str[i] == '|')
		return (1);
	return (0);
}

static char	*extract_operator(char *str, int i, int len)
{
	return (ft_substr(str, i, len));
}

int	process_operator(char *input, int *i, t_token **tokens)
{
	int		len;
	int		type;
	char	*value;
	t_token	*token;

	len = get_operator_len(input, *i);
	type = get_token_type(input, *i);
	value = extract_operator(input, *i, len);
	if (!value)
		return (0);
	token = create_token(value, type);
	if (!token)
	{
		free(value);
		return (0);
	}
	add_token_back(tokens, token);
	*i += len;
	return (1);
}
