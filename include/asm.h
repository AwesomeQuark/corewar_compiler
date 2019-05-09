/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magicwarthog <magicwarthog@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 19:26:11 by conoel            #+#    #+#             */
/*   Updated: 2019/05/09 17:41:55 by magicwartho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include "haflib.h"
# include "lexer.h"
# include "parser.h"

# define TRUE 1
# define FALSE 0

int		parse(t_token *head);
int		transcribe(t_token *head);
int		is_instruction(t_token *token);
int     is_parameter(t_token *token);

#endif
