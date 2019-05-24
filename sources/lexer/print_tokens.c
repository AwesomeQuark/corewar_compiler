/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 13:57:55 by conoel            #+#    #+#             */
/*   Updated: 2019/05/17 16:29:45 by conoel           ###   ########.fr       */
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
	"NAME_CMD",
	"COMMENT_CMP",
	"EOF"
};

void			print_tokens(t_token *head)
{
	next_token(&head);;
	while (head)
	{
		ft_printf("<\033[1m%s\033[0m [\033[31m%s\033[0m]>\n", head->content, definitions[head->type]);
		next_token(&head);;
	}
	write(1, "\n", 1);
}
