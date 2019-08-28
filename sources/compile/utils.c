/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 14:46:06 by conoel            #+#    #+#             */
/*   Updated: 2019/08/28 17:14:33 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			get_type_id(t_token_type type)
{
	int		i;

	i = 0;
	while (g_op_tab[i].type != type)
	{
		if (i == 17)
			break ;
		i++;
	}
	return (i);
}

int			get_byte(t_instruction *actual)
{
	t_instruction	*head;
	int				addr;

	addr = 0;
	head = get_instructions(NULL);
	while (head != NULL)
	{
		if (actual == head)
			return (addr);
		addr += head->byte_len;
		head = head->next;
	}
	return (0);
}
