/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 17:52:11 by conoel            #+#    #+#             */
/*   Updated: 2019/05/08 19:37:53 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include "lexer.h"

int			is_instruction(t_token *token)
{
	if (token->type == LIVE || token->type == LD || token->type == ST
	|| token->type == ADD || token->type == AND || token->type == OR
	|| token->type == ZJMP || token->type == STI || token->type == FORK
	|| token->type == LLD || token->type == LLDI || token->type == LFORK
	|| token->type == AFF)
		return (1);
	else
		return (0);
}

t_ast_node	*new_ast_node(t_ast_node_type type, char *content)
{
	t_ast_node	*new;

	if (!(new = malloc(sizeof(t_ast_node))))
		return (NULL);
	if (!(new->content = ft_strdup(content)))
		return (NULL);
	new->type = type;
	new->parameters = NULL;
	new->next_instruction = NULL;
	return (new);
}

int			parameters_count(t_token *instruction)
{
	t_token	*ptr;
	int		count;
	
	ptr = instruction->next;
	if (instruction->next != STRING)
		return (0);
	while (!is_instruction(ptr) && ptr->type != EOF)
	{
		if (ptr->type != STRING)
			ft_printf("Warning: Invalid parameter %s", ptr->content);
		if (ptr->next->type == SEPARATOR)
			ptr = ptr->next->next;
		count++;
	}
	return (count);
}