/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:41:41 by conoel            #+#    #+#             */
/*   Updated: 2019/06/14 11:04:37 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	g_line = 1;

static t_token_def g_tokens[] =
{
	{"live", 4, LIVE},
	{"ld", 2, LD},
	{"st", 2, ST},
	{"add", 3, ADD},
	{"sub", 3, SUB},
	{"and", 3, AND},
	{"or", 2, OR},
	{"xor", 3, XOR},
	{"zjmp", 4, ZJMP},
	{"ldi", 3, LDI},
	{"sti", 3, STI},
	{"fork", 4, FORK},
	{"lld", 3, LLD},
	{"lldi", 4, LLDI},
	{"lfork", 5, LFORK},
	{"aff", 3, AFF},
	{NAME_CMD_STRING, sizeof(NAME_CMD_STRING) - 1, NAME_CMD},
	{COMMENT_CMD_STRING, sizeof(COMMENT_CMD_STRING) - 1, COMMENT_CMD},
	{NULL, 0, EOF_}
};

void				skip_until_char(char **f, char **last_token, char c)
{
	*last_token += 1;
	*f += 1;
	while (**f != '\0' && **f != c)
		*f += 1;
}

static int			handle_escape(t_token *head, char **f,
	char **last_token)
{
	if (**f == ' ' || **f == '\t' || **f == '\n' || **f == SEPARATOR_CHAR)
	{
		**f == '\n' ? g_line++ : 0;
		if (*last_token != *f)
			add_token(*last_token, *f - *last_token, STRING, head);
		**f == SEPARATOR_CHAR ? add_token(",", 1, SEPARATOR, head) : 0;
		*f += 1;
		*last_token = *f;
		return (1);
	}
	if (**f == '"')
		skip_until_char(f, last_token, '\"');
	else if (**f == '\'')
		skip_until_char(f, last_token, '\'');
	else if (**f == COMMENT_CHAR)
	{
		skip_until_char(f, last_token, '\n');
		*last_token = *f;
	}
	else
		return (0);
	if (*last_token != *f)
		add_token(*last_token, *f - *last_token, STRING, head);
	*last_token = ++(*f);
	return (1);
}

static t_token_def	*search_token_type(char **f, char **last_token,
	t_token *head)
{
	size_t	i;

	i = -1;
	while (g_tokens[++i].type != EOF_)
		if (ft_strncmp(*f, g_tokens[i].content, g_tokens[i].size) == 0
			&& ((*f)[g_tokens[i].size] == ' '
			|| (*f)[g_tokens[i].size] == '\n'
			|| (*f)[g_tokens[i].size] == SEPARATOR_CHAR
			|| (*f)[g_tokens[i].size] == '\0'
			|| (*f)[g_tokens[i].size] == '\t')
			&& *last_token == *f)
			return (&g_tokens[i]);
	if (**f == SEPARATOR_CHAR)
	{
		if (*last_token != *f)
			if (!(add_token(*last_token, *f - *last_token, STRING, head)))
				return (NULL);
		if (!(add_token(*f, 1, SEPARATOR, head)))
			return (NULL);
		*last_token = ++(*f);
		return (search_token_type(f, last_token, head));
	}
	return (NULL);
}

int					lexer_main_loop(char *f, t_token *head)
{
	t_token_def	*current;
	char		*last_tok;

	last_tok = f;
	while (f && *f)
	{
		if (handle_escape(head, &f, &last_tok))
			continue ;
		if (!(current = search_token_type(&f, &last_tok, head)))
		{
			f++;
			continue ;
		}
		if (last_tok != f)
			if (!(add_token(last_tok, f - last_tok, STRING, head)))
				return (0);
		f += current->size;
		last_tok = f;
		if (!(add_token(current->content, current->size, current->type, head)))
			return (0);
	}
	if (last_tok != f && !(f - last_tok == 1 && *last_tok == '\n'))
		if (!(add_token(last_tok, f - last_tok, STRING, head)))
			return (0);
	return (1);
}

t_token				*lexer(char *line)
{
	t_token	*head;

	if (!(head = malloc(sizeof(t_token))))
		return (NULL);
	head->type = START;
	head->next = NULL;
	head->size = 0;
	head->content = NULL;
	if (!(lexer_main_loop(line, head)))
		return (NULL);
	add_token("EOF", 3, EOF_, head);
	return (head);
}
