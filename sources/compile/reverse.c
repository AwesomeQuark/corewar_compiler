/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 22:57:30 by conoel            #+#    #+#             */
/*   Updated: 2019/06/18 22:58:51 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_magic	reverse_bits(t_magic magic)
{
	int		i;
	t_magic tmp;

	tmp = 0;
	i = sizeof(t_magic);
	while (i > 0)
	{
		tmp = tmp << 8;
		tmp += magic & 0xFF;
		magic = magic >> 8;
		i--;
	}
	return (tmp);
}

short	reverse_bits_s(short nb)
{
	int		i;
	short tmp;

	tmp = 0;
	i = sizeof(short);
	while (i > 0)
	{
		tmp = tmp << 8;
		tmp += nb & 0xFF;
		nb = nb >> 8;
		i--;
	}
	return (tmp);
}