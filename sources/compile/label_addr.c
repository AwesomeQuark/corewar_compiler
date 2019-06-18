/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_addr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 10:38:09 by conoel            #+#    #+#             */
/*   Updated: 2019/06/18 23:29:42 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			get_label_addr(char *label_name)
{
	t_instruction	*head;
	int				addr;

	addr = 0;
	head = get_instructions(NULL);
	while (head != NULL)
	{
		if (head->type == LABEL
			&& ft_strcmp(head->args[0]->content, label_name) == 0)
			return (addr);
		addr += head->byte_len;
		head = head->next;
	}
	return (0);
}
