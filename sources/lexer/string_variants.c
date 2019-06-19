/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_variants.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 16:10:21 by conoel            #+#    #+#             */
/*   Updated: 2019/06/19 18:55:30 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int			is_num(char *str)
{
	if (!str)
		return (0);
	if (*str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static size_t		is_label(char *str, char *authorised_chars)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (authorised_chars[j] && str[i])
	{
		if (str[i] == authorised_chars[j])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

t_token_type		identify_string(t_token *token)
{
	t_token_type	type;
	size_t			ret;

	if (token->size > 0 && token->content[token->size - 1] == LABEL_CHAR)
	{
		if ((ret = is_label(token->content, LABEL_CHARS)) != token->size - 1)
		{
			ft_printf("%sWarning%s: Uncorrect char \'%c\' in a label",
				YELLOW, DEF, token->content[ret]);
			ft_printf(" [line %d; char %d]\n", token->line, ret);
		}
		type = LABEL;
	}
	else if (token->content[0] == 'r' && is_num(&(token->content[1])))
		type = REG;
	else if (token->content[0] == DIRECT_CHAR)
		type = DIRECT;
	else if ((token->content[0] == LABEL_CHAR && is_label(token->content + 1, LABEL_CHARS)) || is_num(token->content))
		type = INDIRECT;
	else
		type = STRING;
	return (type);
}
