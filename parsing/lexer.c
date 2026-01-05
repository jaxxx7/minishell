/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 15:08:14 by mhachem           #+#    #+#             */
/*   Updated: 2026/01/05 16:26:43 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_separator(char c)
{
    if (ft_strchr(" |<>", c))
        return (1);
    return (0);
}

t_token *lexer(char *input)
{
    t_token *head;
    t_token *new;
    int     i;
    char    *word;
    char    in_quote;
    int     start;

    head = NULL;
    i = 0;
    while (input[i])
    {
        if (input[i] == ' ')
        {
            i++;
            continue ;
        }
        if (is_separator(input[i]))
        {
            if ((input[i] == '<' && input[i + 1] == '<'))
            {
                new = new_token(5, ft_strdup("<<"));
                i += 2;
            }
            else if ((input[i] == '>' && input[i + 1] == '>'))
            {
                new = new_token(4, ft_strdup(">>"));
                i += 2;
            }
            else
            {
                if (input[i] == '|')
                    new = new_token(PIPE, ft_strdup("|"));
                else if (input[i] == '<')
                    new = new_token(REDIR_IN, ft_strdup("<"));
                else if (input[i] == '>')
                    new = new_token(REDIR_OUT, ft_strdup(">"));
                i++;
            }
        }
        else
        {
            start = i;
            in_quote = 0;
            while (input[i]) 
            {
                if (input[i] == '\"' || input[i] == '\'')
                {
                    if (!in_quote)
                        in_quote = input[i];
                    else if (in_quote == input[i])
                        in_quote = 0;
                    i++;
                }
                else if (is_separator(input[i]))
                {
                    if (in_quote)
                        i++;
                    else
                        break ;
                }
                else
                    i++;
            }
            if (in_quote)
            {
                ft_putstr_fd("Minishell: syntax error: unclosed quotes\n", 2);
                free_tokens(head);
            }
            word = ft_substr(input, start, i - start);
            new = new_token(WORD, word);
        }
        token_add_back(&head, new); 
    }
    return (head);
}

t_token *new_token(int type, char *str)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = str;
	new->next = NULL;
	return (new);
}

void	token_add_back(t_token **head, t_token *new_token)
{
	t_token	*temp;

	if (!head || !new_token)
		return ;
	if (*head == NULL)
	{
		*head = new_token;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_token;
}
