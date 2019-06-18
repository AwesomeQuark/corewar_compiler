/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:28:10 by conoel            #+#    #+#             */
/*   Updated: 2019/06/14 10:58:20 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*before_last_token(t_token *head)
{
	if (!head || !head->next)
		return (NULL);
	while (head->next->next != NULL)
		next_token(&head);
	return (head);
}

static t_token	*last_token(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next != NULL)
		next_token(&head);
	return (head);
}

int				add_token(char *content, size_t size, t_token_type type,
		t_token *head)
{
	t_token	*new;
	t_token	*last;

	if (!(new = malloc(sizeof(t_token))))
		return (0);
	if (!(new->content = ft_memdup(content, size)))
		return (0);
	new->size = size;
	new->type = type;
	new->next = NULL;
	new->line = g_line;
	if (!(last = last_token(head)))
		return (0);
	if (type == STRING && (last->type != COMMENT_CMD && last->type != NAME_CMD))
		new->type = identify_string(new);
	if (type == STRING && (last->type == NAME_CMD || last->type == COMMENT_CMD))
	{
		new->type = last->type - 2;
		last = before_last_token(head);
		last->next->next = NULL;
		release_tokens(last->next);
	}
	last->next = new;
	return (1);
}

void			release_tokens(t_token *head)
{
	t_token *tmp;

	if (!head)
		return ;
	while (head)
	{
		if (head->content)
			free(head->content);
		tmp = head;
		next_token(&head);
		free(tmp);
	}
}

void			next_token(t_token **current)
{
	if (!current || !*current)
		return ;
	*current = (*current)->next;
}
