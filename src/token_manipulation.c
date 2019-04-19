/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_manipulation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:28:10 by conoel            #+#    #+#             */
/*   Updated: 2019/04/09 17:37:06 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*last_token(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next != NULL)
		head = head->next;
	return (head);
}

int				add_token(char *content, size_t size, t_token_type type, t_token *head)
{
	t_token	*new;
	t_token	*last;

	if (!(new = malloc_garbage(sizeof(t_token))))
		return (0);
	new->content = ft_memdup(content, size);
	new->size = size;
	new->type = type;
	new->next = NULL;
	if (!(last = last_token(head)))
		return (0);
	last->next = new;
	return (1);
}

t_token_type	misc_type(char *str, size_t size)
{
	size_t	i;

	i = 0;
	while (str[i] && size--)
		if (!ft_isdigit(str[i]))
			return (MISC_STRING);
	return (MISC_INT);
}
