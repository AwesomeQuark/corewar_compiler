/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 11:07:57 by conoel            #+#    #+#             */
/*   Updated: 2019/05/20 14:36:19 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "haflib.h"
#include "lexer.h"

typedef struct	s_instruction
{
	struct s_instruction	*next;
	t_token_type			type;
	t_token					**args;
	int						argc;
}				t_instruction;

extern t_op g_op_tab[17];

t_instruction		*new_instruction(t_instruction *head, t_token_type type, int argc);
t_instruction		*get_instructions(t_instruction *new);
void				release_instructions(void);
t_instruction		*last_instruction(t_instruction *head);

#endif