/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:28:10 by conoel            #+#    #+#             */
/*   Updated: 2019/05/17 14:11:14 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*before_last_token(t_token *head)
{
	if (!head || !head->next)
		return (NULL);
	while (head->next->next != NULL)
		head = head->next;
	return (head);
}

static t_token	*last_token(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next != NULL)
		head = head->next;
	return (head);
}

int				add_token(char *content, size_t size, t_token_type type,
		t_token *head)
{
	t_token	*new;
	t_token	*last;

	if (!(new = malloc(sizeof(t_token))))
		return (0);
	new->content = ft_memdup(content, size);
	new->size = size;
	new->type = type;
	new->type = type;
	new->next = NULL;
	new->line = g_line;
	if (!(last = last_token(head)))
		return (0);
	if (type == STRING)
		new->type = identify_string(new);
	if (new->type == STRING && (last->type == NAME || last->type == COMMENT))
	{
		new->type = last->type;
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
		head = head->next;
		free(tmp);
	}
}

void skip_until_char(char **file, char **last_token, char c)
{
	*last_token += 1;
	*file += 1;
	while (**file != '\0' && **file != c)
		*file += 1;
}
