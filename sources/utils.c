/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 13:55:33 by conoel            #+#    #+#             */
/*   Updated: 2020/02/12 18:44:23 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		quit(char *file_name, t_token *token_head, char *msg, int ret_value)
{
	free(file_name);
	if (token_head)
		release_tokens(token_head);
	if (msg)
		ft_putstr_fd(msg, 2);
	return (ret_value);
}

int		is_instruction(t_token *token)
{
	t_token_type t;

	t = token->type;
	if (t >= LIVE && t <= AFF)
		return (TRUE);
	else
		return (FALSE);
}

int		is_parameter(t_token *token, int choice)
{
	t_token_type	t;

	t = token->type;
	if (t == DIRECT && (choice & T_DIR))
		return (TRUE);
	if (t == REG && (choice & T_REG))
		return (TRUE);
	if (t == INDIRECT && (choice & T_IND))
		return (TRUE);
	else
		return (FALSE);
}
