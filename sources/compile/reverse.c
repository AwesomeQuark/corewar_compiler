/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 22:57:30 by conoel            #+#    #+#             */
/*   Updated: 2019/08/28 17:12:14 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

unsigned int	reverse_bits(unsigned int nb)
{
	int				i;
	unsigned int	tmp;

	tmp = 0;
	i = sizeof(unsigned int);
	while (i > 0)
	{
		tmp = tmp << 8;
		tmp += nb & 0xFF;
		nb = nb >> 8;
		i--;
	}
	return (tmp);
}

short			reverse_bits_s(short nb)
{
	int		i;
	short	tmp;

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
