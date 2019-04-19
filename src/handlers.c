/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:14:28 by conoel            #+#    #+#             */
/*   Updated: 2019/04/10 17:19:04 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "haf.h"

int		jew_handler(t_token *head, t_haf_var *variables)
{
	if (head == NULL || head->next == NULL || head->next->next == NULL)
		return (return_("Error [jood] : ???"));
	if (head->next->type != MISC_STRING || head->next->next->type != MISC_INT)
		return (return_("Error [jood] : Type error"));
	return (variable_add(variables, head->next->content, (t_var)ft_atoi(head->next->next->content), INT));
}

int		print_handler(t_token *head, t_haf_var *variables)
{
	t_token		*arg1_token;
	t_haf_var	*arg1_var;

	if (head == NULL || head->next == NULL)
		return (return_("Error [AnneFrank] : ???"));
	if (head->next->type != MISC_STRING && head->next->type != MISC_INT && head->next->type != OPENING_BRACKET)
		return (return_("Error [AnneFrank] : Type error"));
	arg1_token = head->next;
	if (head->next->type == OPENING_BRACKET)
		if (!(calculator(head, variables)))
			return (0);
	if (head->next->type == MISC_STRING)
	{
		if (!(arg1_var = variable_get(variables, arg1_token->content, arg1_token->size)))
			return (0);
		ft_printf("%d\n", arg1_var->content.int_);
	}
	else
		ft_printf("%s\n", arg1_token->content);
	return (1);
}

int		add_handler(t_token *head, t_haf_var *variables)
{
	t_token		*arg1_token;
	t_token		*arg2_token;
	t_haf_var	*arg1_var;
	t_haf_var	*arg2_var;

	if (head == NULL || head->next == NULL || head->next->next == NULL)
		return (return_("Error [optellen] : ???"));
	arg1_token = head->next;
	arg2_token = head->next->next;
	if (arg1_token->type != MISC_STRING || (arg2_token->type != MISC_STRING && arg2_token->type != MISC_INT))
		return (return_("Error [optellen] : Type error"));
	if (!(arg1_var = variable_get(variables, arg1_token->content, arg1_token->size)))
		return (return_("Error [optellen] : Cannot find arg1 variable"));
	if (arg2_token->type == MISC_INT)
	{
		arg1_var->content.int_ += ft_atoi(arg2_token->content);
	}
	if (arg2_token->type == MISC_STRING)
	{
		if (!(arg2_var = variable_get(variables, arg2_token->content, arg2_token->size)))
			return (return_("Error [optellen] : Cannot find arg2 variable"));
		arg1_var->content.int_ += arg2_var->content.int_;
	}
	return (1);
}