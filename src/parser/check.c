/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magicwarthog <magicwarthog@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 18:49:34 by magicwartho       #+#    #+#             */
/*   Updated: 2019/05/09 19:15:45 by magicwartho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int     parameter_check(t_token *token)
{
    if (!is_instruction(token->next) && token->next->type != EOF_ && token->next->type != LABEL && token->next->type != SEPARATOR)
        ft_printf("Warning: expected new instruction, separator or EOF (%s) [line %d]\n", token->next->content, token->next->line);
    return (1);
}

int		label_check(t_token *token)
{
		if ((!is_instruction(token->next) && token->next->type != EOF_))
			ft_printf("Warning: syntax error (%s) [line %d]\n", token->next->content, token->line);
		return (1);
}

int		separator_check(t_token *token)
{
		if (!is_parameter(token->next))
			ft_printf("Warning: parameter expected [line %d]\n", token->line);
		return (1);
}