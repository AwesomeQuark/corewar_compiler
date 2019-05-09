/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magicwarthog <magicwarthog@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:28:20 by magicwartho       #+#    #+#             */
/*   Updated: 2019/05/09 18:53:58 by magicwartho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H 


typedef struct  s_parser_functions
{
    t_token_type    type;
    int             (*checker)(t_token *token);
}               t_parser_functions;

int     parameter_check(t_token *token);
int		label_check(t_token *token);
int		separator_check(t_token *token);

# endif