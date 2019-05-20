/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 19:26:11 by conoel            #+#    #+#             */
/*   Updated: 2019/05/20 13:17:59 by conoel           ###   ########.fr       */
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
int		compile(t_token *head, char *file_name_s);
int		is_instruction(t_token *token);
int		is_parameter(t_token *token, int choices);

#endif
