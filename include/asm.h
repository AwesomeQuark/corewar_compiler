/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 19:26:11 by conoel            #+#    #+#             */
/*   Updated: 2019/05/07 20:17:42 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

#include <fcntl.h>
#include "haflib.h"
#include "lexer.h"

int		parse(t_token *head);
void	transcribe(t_token *head);

#endif
