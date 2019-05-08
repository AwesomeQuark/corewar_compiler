/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:35:16 by conoel            #+#    #+#             */
/*   Updated: 2019/05/08 18:28:15 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

#include <stdlib.h>

typedef enum
{
	AST_START,
	AST_INSTRUCTION,
	AST_LABEL,
	AST_DIRECT,
	AST_INDIRECT,
	AST_COMMENT,
	AST_NAME,
	AST_SEPARATOR,
	AST_END
}	t_ast_node_type;

typedef struct		s_ast
{
	t_ast_node_type	type;
	char			*content;
	struct s_ast	*next_instruction;
	struct s_ast	**parameters;
}					t_ast_node;


t_ast_node		*build_ast(t_token *token_head);

t_ast_node		*new_ast_node(t_ast_node_type type, char *content);
int				is_instruction(t_token *token);

#endif