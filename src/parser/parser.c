/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:27:34 by magicwartho       #+#    #+#             */
/*   Updated: 2019/05/17 16:27:15 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op g_op_tab[17];

static int		skip_start(t_token **head)
{
	t_token	*current;

	current = *head;
	next_token(&current);
	if (current->type != NAME)
		return (return_("Error: Missing name marker"));
	next_token(&current);
//	if (current->type != STRING)
//		return (return_("Error: Missing name content"));
//	next_token(&current);
	if (current->type != COMMENT)
		return (return_("Error: Missing comment marker"));
	next_token(&current);
//	if (current->type != STRING)
//		return (return_("Error: Missing comment content"));
	*head = current;
	return (TRUE);
}

static t_token *scan_instruction(t_op op, t_token *head)
{
	size_t	i;

	i = 0;
	ft_printf("%s%sOperation:%s %s%-*s%s  [ ", "\033[4m", BOLD, DEF, GREEN, 7, head->content, DEF);
	next_token(&head);;
	while (op.argc)
	{
		if (!is_parameter(head, op.args[i++]))
		{
			ft_printf("%sError:%s Expected argument, instead found \"%s\" [line %d]\n", RED, DEF, head->content, head->line);
			return (FALSE);
		}
		ft_printf(" %s%s%s ", YELLOW, head->content, DEF);
		op.argc--;
		if (op.argc)
			next_token(&head);;
		if (op.argc && head->type != SEPARATOR)
		{
			ft_printf("%sError:%s Expected separator, instead found \"%s\" [line %d]\n", RED, DEF, head->content, head->line);
			return (FALSE);
		}
		else if (op.argc)
			next_token(&head);;
	}
	ft_printf("]\n");
	return (head);
}

int			parse(t_token *head)
{
	size_t	i;

	if (!skip_start(&head))
		return (FALSE);
	while (head)
	{
		i = 0;
		if (head->type == EOF_)
			break ;
		if (head->type != LABEL && head->type != NAME && head->type != COMMENT)
		{
			while (g_op_tab[i].type != head->type)
			{
				if (i == 17)
				{
					ft_printf("%sError:%s Unexpected keyword \"%s\" [line %d]\n",
						RED, DEF, head->content, head->line);
					return (FALSE);
					i = 0;
					next_token(&head);;
				}
				i++;
			}
			head = scan_instruction(g_op_tab[i], head);
		}
		if (head)
			next_token(&head);;
	}
	return (TRUE);
}