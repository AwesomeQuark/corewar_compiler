/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 17:14:29 by conoel            #+#    #+#             */
/*   Updated: 2019/04/10 15:41:04 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../haflib/includes/haflib.h"

typedef enum
{
	START,         // Head marker
	//### CONTROL SYMBOLS ###
	OPENING_BRACE,
	CLOSING_BRACE,
	OPENING_PARENTHESE,
	CLOSING_PARENTHESE,
	OPENING_BRACKET, // Brackets indicate a calculation
	CLOSING_BRACKET,
	//### OPERATORS ###
	PLUS,
	MINUS,
	DIVIDE,
	MULTIPLY,
	//### COMMANDS ###
	JEW,            // Declaration int
	ADD,            // Operator
	PRINT,          // Basic print command
	MISC_STRING,    // Variable and function names
	MISC_INT,       // Just a raw int
	STOP            // End of the array
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

t_token			*lexer(int fd);
int				add_token(char *content, size_t size, t_token_type type, t_token *head);
t_token_type	misc_type(char *str, size_t size);

#endif