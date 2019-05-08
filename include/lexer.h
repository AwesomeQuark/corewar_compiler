/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 17:14:29 by conoel            #+#    #+#             */
/*   Updated: 2019/05/08 18:20:22 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "haflib.h"
# include "op.h"

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