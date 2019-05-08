/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:28:10 by conoel            #+#    #+#             */
/*   Updated: 2019/05/08 18:21:55 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*last_token(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next != NULL)
		head = head->next;
	return (head);
}

int				add_token(char *content, size_t size, t_token_type type,
		t_token *head)
{
	t_token	*new;
	t_token	*last;

	if (!(new = malloc(sizeof(t_token))))
		return (0);
	new->content = ft_memdup(content, size);
	new->size = size;
	new->type = type;
	new->next = NULL;
	if (!(last = last_token(head)))
		return (0);
	last->next = new;
	if (type == STRING)
	{
		if (size > 0 && content[size - 1] == LABEL_CHAR)
			new->type = LABEL;
		else if (content[0] == 'r')
			new->type = REG;
		else if (content[0] == DIRECT_CHAR)
			new->type = DIRECT;
	}
	return (1);
}

void			release_tokens(t_token *head)
{
	t_token *tmp;

	if (!head)
		return ;
	while (head)
	{
		if (head->content)
			free(head->content);
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

static char *definitions[] =
{
	"START",
	"LIVE",
	"LD",
	"ST",
	"ADD",
	"AND",
	"OR",
	"ZJMP",
	"STI",
	"FORK",
	"LLD",
	"LLDI",
	"LFORK",
	"AFF",
	"LABEL",
	"REG",
	"DIRECT",
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
		ft_printf("<\033[1m%s\033[0m [\033[31m%s\033[0m]> ", head->content, definitions[head->type]);
		head = head->next;
	}
	write(1, "\n", 1);
}

void skip_until_char(char **file, char **last_token, char c)
{
	*last_token += 1;
	*file += 1;
	while (**file != '\0' && **file != c)
		*file += 1;
}
