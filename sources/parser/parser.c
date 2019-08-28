/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:27:34 by magicwartho       #+#    #+#             */
/*   Updated: 2019/08/28 14:59:26 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		add_instruction(t_op op, t_token *head)
{
	t_instruction	*new;
	int				i;

	i = 0;
	new = get_instructions(NULL);
	new = last_instruction(new);
	if (!(new_instruction(new, head->type, op.argc)))
		return (FALSE);
	new = new->next;
	while (i < op.argc)
	{
		head = head->next;
		new->args[i] = head;
		head = head->next;
		i++;
	}
	new->byte_len = line_byte_len(new);
	ft_printf(" <%s%d%s>\n", RED, new->byte_len, DEF);
	return (TRUE);
}

static int		skip_start(t_token **head)
{
	t_token	*current;

	current = *head;
	next_token(&current);
	if (current->type != NAME)
	{
		ft_printf("\n%sError:%s Missing name marker", RED, DEF);
		return (FALSE);
	}
	next_token(&current);
	if (current->type != COMMENT)
	{
		ft_printf("\n%sError:%s Missing comment marker", RED, DEF);
		return (FALSE);
	}
	next_token(&current);
	*head = current;
	return (TRUE);
}

static t_token	*scan_instruction(t_op op, t_token *head)
{
	size_t	i;

	i = 0;
	ft_printf("%s%sOperation:%s %s%-*s%s  [", "\033[4m", BOLD, DEF, GREEN,
		7, head->content, DEF);
	next_token(&head);
	while (op.argc)
	{
		if (!is_parameter(head, op.args[i++]))
		{
			ft_printf("\n%sError:%s Bad argument type, found \"%s\" [l %d]\n"
				, RED, DEF, head->content, head->line);
			return (FALSE);
		}
		ft_printf(" %s%s%s ", YELLOW, head->content, DEF);
		--op.argc ? next_token(&head) : 0;
		if (op.argc && head->type != SEPARATOR)
		{
			ft_printf("\n%sError:%s Expected separator, found \"%s\" [l %d]\n"
				, RED, DEF, head->content, head->line);
			return (FALSE);
		}
		op.argc ? next_token(&head) : 0;
	}
	ft_printf("]");
	return (head);
}

static int		get_type(t_token *current)
{
	int		i;

	i = 0;
	while (g_op_tab[i].type != current->type)
	{
		if (i == 17)
		{
			ft_printf("\n%sError:%s Unexpected keyword \"%s\" [line %d]\n",
				RED, DEF, current->content, current->line);
			return (-1);
		}
		i++;
	}
	return (i);
}

int				parse(t_token *head)
{

	t_token	*mem;
	int		i;

	get_instructions(new_instruction(NULL, START, 0));
	if (!skip_start(&head))
		return (FALSE);
	while (head)
	{
		if (head->type == EOF_)
			break ;
		if (head->type != LABEL && head->type != NAME && head->type != COMMENT)
		{
			if ((i = get_type(head)) == -1)
				return (FALSE);
			mem = head;
			if (!(head = scan_instruction(g_op_tab[i], head)))
				return (FALSE);
			if (!(add_instruction(g_op_tab[i], mem)))
				return (FALSE);
		}
		if (head && head->type == LABEL)
		{
			add_label(last_instruction(get_instructions(NULL)), head);
			ft_printf("%s%sLabel:%s %s%-*s%s\n", "\033[4m"
				, BOLD, DEF, GREEN, 7, head->content, DEF);
		}
		if (head)
			next_token(&head);
	}
	return (TRUE);
}
