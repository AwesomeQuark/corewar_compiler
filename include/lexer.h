/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magicwarthog <magicwarthog@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 17:14:29 by conoel            #+#    #+#             */
/*   Updated: 2019/05/09 17:57:30 by magicwartho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "haflib.h"
# include "op.h"

extern int	g_line;

typedef enum
{
	START,
	LIVE,
	LD,
	ST,
	ADD,
	AND,
	OR,
	ZJMP,
	STI,
	FORK,
	LLD,
	LLDI,
	LFORK,
	AFF,
	LABEL,
	REG,
	DIRECT,
	STRING,
	SEPARATOR,
	NAME,
	COMMENT,
	EOF_
} t_token_type;

typedef struct s_token_def
{
	char*			content;
	size_t			size;
	t_token_type	type;
}				t_token_def;

typedef struct s_token
{
	struct s_token	*next;
	char*			content;
	size_t			size;
	t_token_type	type;
	int				line;
}				t_token;


/*
**	EXTERNAL
*/
t_token			*lexer(char *line);
void			print_tokens(t_token *head);
void			release_tokens(t_token *head);

/*
**	INTERNAL
*/
int				add_token(char *content, size_t size, t_token_type type, t_token *head);
void			skip_until_char(char **file, char **last_token, char c);

#endif
