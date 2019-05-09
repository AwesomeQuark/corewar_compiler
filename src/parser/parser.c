/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magicwarthog <magicwarthog@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:27:34 by magicwartho       #+#    #+#             */
/*   Updated: 2019/05/09 18:56:58 by magicwartho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_parser_functions handlers[] =
{
	{START, NULL},
	{LIVE, NULL},
	{LD, NULL},
	{ST, NULL},
	{ADD, NULL},
	{AND, NULL},
	{OR, NULL},
	{ZJMP, NULL},
	{STI, NULL},
	{FORK, NULL},
	{LLD, NULL},
	{LLDI, NULL},
	{LFORK, NULL},
	{AFF, NULL},
	{LABEL, &label_check},
	{REG, &parameter_check},
	{DIRECT, &parameter_check},
	{STRING, NULL},
	{SEPARATOR, &separator_check},
	{NAME, NULL},
	{COMMENT, NULL},
	{EOF_, NULL}
};


int	parse(t_token *head)
{
	size_t	i;

	while (head)
	{
		i = 0;
		while (handlers[i].type != EOF_)
		{
			if (head->type == handlers[i].type && handlers[i].checker != NULL)
				if (!(handlers[i].checker(head)))
					return (0);
			i++;
		}
		head = head->next;
	}
	return (1);
}
