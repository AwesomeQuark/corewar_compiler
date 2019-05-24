/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:27:34 by magicwartho       #+#    #+#             */
/*   Updated: 2019/05/20 14:35:32 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		add_instruction(t_op op, t_token *head)
{
	t_instruction	*new;
	int				i;

	i = 0;
	new = get_instructions(NULL);
	new = last_instruction(new);
	new_instruction(new, head->type, op.argc);
	new = new->next;
	while (i < op.argc)
	{
		head = head->next;
		new->args[i] = head;
		head = head->next;
		i++;
	}
}

static int		skip_start(t_token **head)
{
	t_token	*current;

	current = *head;
	next_token(&current);
	if (current->type != NAME)
	{
		ft_printf("%sError:%s Missing name marker", RED, DEF);
		return (FALSE);
	}
	next_token(&current);
	if (current->type != COMMENT)
	{
		ft_printf("%sError:%s Missing comment marker", RED, DEF);
		return (FALSE);
	}
	next_token(&current);
	*head = current;
	return (TRUE);
}

static t_token *scan_instruction(t_op op, t_token *head)
{
	size_t	i;

	i = 0;
	ft_printf("%s%sOperation:%s %s%-*s%s  [", "\033[4m", BOLD, DEF, GREEN, 7, head->content, DEF);
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

static int	get_type(t_token *current)
{
	int		i;

	i = 0;
	while (g_op_tab[i].type != current->type)
	{
		if (i == 17)
		{
			ft_printf("%sError:%s Unexpected keyword \"%s\" [line %d]\n",
				RED, DEF, current->content, current->line);
			return (-1);
		}
		i++;
	}
	return (i);
}

int			parse(t_token *head)
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
			head = scan_instruction(g_op_tab[i], head);
			add_instruction(g_op_tab[i], mem);
		}
		if (head)
			next_token(&head);;
	}
	return (TRUE);
}
