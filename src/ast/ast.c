/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:57:23 by conoel            #+#    #+#             */
/*   Updated: 2019/05/08 19:37:55 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include "lexer.h"

t_ast_node		*next_instruction(t_token **ptr)
{
	t_ast_node	*new;
	size_t		parameters_nb;

	if ((*ptr)->type == LABEL)
		ptr = (*ptr)->next;
	if (!is_instruction(ptr))
		ft_printf("Warning: Invalid instruction %s", (*ptr)->content);
	if (!(new = new_ast_node(AST_INSTRUCTION, (*ptr)->content)))
		return ((void *)return_("Error: malloc (next_instruction, ast.c)"));
	if ((parameters_nb == parameters_count(*ptr)) == -1)
		return (NULL);
	//if (!(new->parameters = malloc(sizeof(void *) * parameters_nb)))
	
}

t_ast_node		*build_ast(t_token *token_head)
{
	t_ast_node	*instructions;
	t_token		*ptr;
	char		failure;

	failure = 0;
	if (!(instructions = new_ast_node(START, NULL)))
		return ((void *)return_("Error: malloc (build_ast, ast.c)"));
	while (ptr != EOF)
	{
		instructions->next_instruction = next_instruction(&ptr);
		if (instructions->next_instruction)
			instructions = instructions->next_instruction;
		else
			failure = 1;
	}
	if (failure)
		return (NULL);
	else
		return (instructions);
}
