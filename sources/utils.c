/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 13:55:33 by conoel            #+#    #+#             */
/*   Updated: 2019/05/17 13:55:37 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	is_instruction(t_token *token)
{
	t_token_type t;

	t = token->type;
	if (t >= LIVE && t <= AFF)
		return (TRUE);
	else
		return (FALSE);
}

int	is_parameter(t_token *token, int choice)
{
	t_token_type	t;

	t = token->type;
	if (t == DIRECT && choice & T_DIR)
		return (TRUE);
	if (t == REG && choice & T_REG)
		return (TRUE);
	if (t == INDIRECT && choice & T_IND)
		return (TRUE);
	else
		return (FALSE);
}
