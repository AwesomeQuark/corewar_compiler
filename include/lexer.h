/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 17:14:29 by conoel            #+#    #+#             */
/*   Updated: 2019/06/26 14:21:50 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "haflib.h"
# include "op.h"

extern int		g_line;

typedef enum
{
	START,
	LIVE,
	LD,
	ST,
	ADD,
	SUB,
	AND,
	OR,
	XOR,
	ZJMP,
	LDI,
	STI,
	FORK,
	LLD,
	LLDI,
	LFORK,
	AFF,
	LABEL,
	REG,
	DIRECT,
	INDIRECT,
	STRING,
	SEPARATOR,
	NAME,
	COMMENT,
	NAME_CMD,
	COMMENT_CMD,
	EOF_
}	t_token_type;

typedef struct	s_token_def
{
	char			*content;
	size_t			size;
	t_token_type	type;
}				t_token_def;

typedef struct	s_token
{
	struct s_token	*next;
	char			*content;
	size_t			size;
	t_token_type	type;
	int				line;
}				t_token;

typedef struct	s_op
{
	t_token_type	type;
	int				argc;
	int				args[4];
	int				opcode;
	int				cycles;
	char			*description;
	char			ocp;
	char			unknown;
}				t_op;

/*
**	EXTERNAL
*/
t_token			*lexer(char *line);
void			print_tokens(t_token *head);
void			release_tokens(t_token *head);
void			next_token(t_token **current);

/*
**	INTERNAL
*/
int				add_token(char *content, size_t size,
					t_token_type type, t_token *head);
void			skip_until_char(char **file, char **last_token, char c);
t_token_type	identify_string(t_token *token);

#endif
