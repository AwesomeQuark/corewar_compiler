/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 13:57:55 by conoel            #+#    #+#             */
/*   Updated: 2019/05/17 13:58:16 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char *definitions[] =
{
	"START",
	"LIVE",
	"LD",
	"ST",
	"ADD",
	"SUB",
	"AND",
	"OR",
	"XOR",
	"ZJMP",
	"LDI",
	"STI",
	"FORK",
	"LLD",
	"LLDI",
	"LFORK",
	"AFF",
	"LABEL",
	"REG",
	"DIRECT",
	"INDIRECT",
	"STRING",
	"SEPARATOR",
	"NAME",
	"COMMENT",
	"EOF"
};

void			print_tokens(t_token *head)
{
	head = head->next;
	while (head)
	{
		ft_printf("<\033[1m%s\033[0m [\033[31m%s\033[0m]>\n", head->content, definitions[head->type]);
		head = head->next;
	}
	write(1, "\n", 1);
}
