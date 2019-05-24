/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:41:41 by conoel            #+#    #+#             */
/*   Updated: 2019/05/17 16:39:24 by conoel           ###   ########.fr       */
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

void skip_until_char(char **file, char **last_token, char c)
{
	*last_token += 1;
	*file += 1;
	while (**file != '\0' && **file != c)
		*file += 1;
}

static int			handle_escape(t_token *head, char **file,
	char **last_token)
{
	if (**file == ' ' || **file == '\t' || **file == '\n' || **file == SEPARATOR_CHAR)
	{
		if (**file == '\n')
			g_line++;
		if (*last_token != *file)
			add_token(*last_token, *file - *last_token, STRING, head);
		if (**file == SEPARATOR_CHAR)
			add_token(",", 1, SEPARATOR, head);
		*file += 1;
		*last_token = *file;
		return (1);
	}
	if (**file == '"')
		skip_until_char(file, last_token, '\"');
	else if (**file == '\'')
		skip_until_char(file, last_token, '\'');
	else if (**file == COMMENT_CHAR)
	{
		skip_until_char(file, last_token, '\n');
		*last_token = *file;
	}
	else
		return (0);
	if (*last_token != *file)
		add_token(*last_token, *file - *last_token, STRING, head);
	*file += 1;
	*last_token = *file;
	return (1);
}

static t_token_def	*search_token_type(char **file, char **last_token,
	t_token *head)
{
	size_t	i;

	i = 0;
	while (g_tokens[i].type != EOF_)
	{
		if (ft_strncmp(*file, g_tokens[i].content, g_tokens[i].size) == 0
			&& ((*file)[g_tokens[i].size] == ' '
			|| (*file)[g_tokens[i].size] == '\n'
			|| (*file)[g_tokens[i].size] == SEPARATOR_CHAR
			|| (*file)[g_tokens[i].size] == '\0'
			|| (*file)[g_tokens[i].size] == '\t')
			&& *last_token == *file)
			return (&g_tokens[i]);
		i++;
	}
	if (**file == SEPARATOR_CHAR)
	{
		if (*last_token != *file)
			add_token(*last_token, *file - *last_token, STRING, head);
		add_token(*file, 1, SEPARATOR, head);
		*file += 1;
		*last_token = *file;
		return (search_token_type(file, last_token, head));
	}
	return (NULL);
}

int					lexer_main_loop(char *file, t_token *head)
{
	t_token_def	*current;
	char		*last_token_found;

	last_token_found = file;
	while (file && *file)
	{
		if (handle_escape(head, &file, &last_token_found))
			continue ;
		if (!(current = search_token_type(&file, &last_token_found, head)))
		{
			file++;
			continue ;
		}
		if (last_token_found != file)
			add_token(last_token_found, file - last_token_found, STRING, head);
		file += current->size;
		last_token_found = file;
		if (!(add_token(current->content, current->size, current->type, head)))
			return (0);
	}
	if (last_token_found != file && !(file - last_token_found == 1
		&& *last_token_found == '\n'))
		add_token(last_token_found, file - last_token_found, STRING, head);
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
	lexer_main_loop(line, head);
	add_token("EOF", 3, EOF_, head);
	return (head);
}
