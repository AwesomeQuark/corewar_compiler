/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_byte_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 13:49:22 by conoel            #+#    #+#             */
/*   Updated: 2019/08/28 16:07:42 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	get_type(t_token_type type)
{
	int		i;

	i = 0;
	while (g_op_tab[i].type != type)
	{
		if (i == 17)
			break;
		i++;
	}
	return (i);
}

static int	param_encoding(t_token *param, int type)
{
	int	len;

	len = 0;
	if (param->type == REG)
		len++;
	if (param->type == DIRECT)
	{
		if (param->content[1] == ':' || (type >= 9 && type <= 15 && type != 13))
			len += 2;
		else
			len += 4;
	}
	if(param->type == INDIRECT)
		len += 2;
	return (len);
}

int			line_byte_len(t_instruction *actual)
{
	int		len;
	int		i;
	int		type;

	i = 0;
	len = 1;
	type = get_type(actual->type);
	if (g_op_tab[type].ocp)
		len++;
	while (i < actual->argc)
	{
		len += param_encoding(actual->args[i], type);
		i++;
	}
	return (len);
}
