/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 19:26:11 by conoel            #+#    #+#             */
/*   Updated: 2020/02/12 17:28:56 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include "parser.h"

# define TRUE 1
# define FALSE 0
# define US1 "Usage:\t./asm [champion_name].s\n"
# define US2 "\t./asm -src [champion_name].s -dest [compiled_file].cor"
# define USAGE US1 US2

int		parse(t_token *head);
int		transcribe(t_token *head);
int		compile(t_token *head, char *file_name_s);

int		add_line(int fd, t_instruction *actual);
t_magic	reverse_bits(t_magic magic);
short	reverse_bits_s(short nb);

/*
**	UTILS
*/
int		is_instruction(t_token *token);
int		is_parameter(t_token *token, int choices);
int		get_label_addr(char *label_name);
int		get_type_id(t_token_type type);
int		get_byte(t_instruction *actual);

int 	quit(char *file_name, t_token *token_head, char *msg, int ret_value);

#endif
