/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 11:07:43 by conoel            #+#    #+#             */
/*   Updated: 2019/08/28 17:44:41 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_instruction	*new_instruction(t_instruction *last,
	t_token_type type, int argc)
{
	t_instruction	*new;

	if (!(new = malloc(sizeof(t_instruction))))
		return (NULL);
	new->type = type;
	new->argc = argc;
	new->next = NULL;
	new->byte_len = 0;
	if (!(new->args = malloc(sizeof(t_token *) * argc)))
		return (NULL);
	if (last)
		last->next = new;
	return (new);
}

t_instruction	*get_instructions(t_instruction *new)
{
	static t_instruction	*head = NULL;

	if (new)
		head = new;
	else
		return (head);
	return (NULL);
}

void			release_instructions(void)
{
	t_instruction	*head;
	t_instruction	*tmp;

	head = get_instructions(NULL);
	while (head)
	{
		tmp = head->next;
		free(head->args);
		free(head);
		head = tmp;
	}
}

t_instruction	*last_instruction(t_instruction *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

t_instruction	*add_label(t_instruction *last, t_token *label)
{
	t_instruction	*new;

	new = new_instruction(last, LABEL, 1);
	label->content[ft_strlen(label->content) - 1] = '\0';
	new->args[0] = label;
	return (new);
}
