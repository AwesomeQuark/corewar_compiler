/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 13:49:22 by conoel            #+#    #+#             */
/*   Updated: 2019/08/28 16:25:56 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		write_number_to_memory(int *len, char *buff, int nb, int bytes)
{
	if (bytes == 4)
		nb = reverse_bits(nb);
	else if (bytes == 2)
		nb = reverse_bits_s(nb);
	while (bytes-- > 0)
	{
		buff[(*len)++] = nb & 0xFF;
		nb = nb >> 8;
	}	
}

static int	param_encoding(t_token *param, int *len, char *buff, int byte)
{
	if (param->type == REG)
		write_number_to_memory(len, buff, ft_atoi(&param->content[1]), 1);
	if (param->type == DIRECT)
	{
		if (param && param->content && param->content[1] == LABEL_CHAR)
			write_number_to_memory(len, buff, get_label_addr(&(param->content[2])) - byte, 2);
		else
			write_number_to_memory(len, buff, ft_atoi(&(param->content[1])), 4);
	}
	if (param->type == INDIRECT)
	{
		if (param->content[0] == LABEL_CHAR)
			write_number_to_memory(len, buff, 0, 2);
		else
			write_number_to_memory(len, buff, ft_atoi(param->content), 2);
	}
	return (TRUE);
}

static char	ocp(t_token_type param, int i)
{
	int	ocp;

	ocp = 0;
	if (param == REG)
		ocp = 4;
	else if (param == DIRECT)
		ocp = 8;
	else if (param == INDIRECT)
		ocp = 12;
	while (i++ < 2)
		ocp = ocp * 4;
	return (ocp);
}

int			add_line(int fd, t_instruction *actual)
{
	char	*buff;
	int		len;
	int		i;
	int		type;

	if (!(buff = malloc(64)))
		return (FALSE);
	len = 1;
	type = get_type_id(actual->type);
	buff[0] = g_op_tab[type].opcode;
	if (g_op_tab[type].ocp)
		buff[len++] = 0;
	i = 0;
	while (i < actual->argc)
	{
		if (!(param_encoding(actual->args[i], &len, buff, get_byte(actual))))
			return (FALSE);
		if (g_op_tab[type].ocp)
			buff[1] += ocp(actual->args[i]->type, i);
		i++;
	}
	write(fd, buff, len);
	free(buff);
	return (TRUE);
}
