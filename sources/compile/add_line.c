/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 13:49:22 by conoel            #+#    #+#             */
/*   Updated: 2019/05/24 17:44:20 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	get_type(t_token_type type)
{
	int		i;

	i = 0;
	while (g_op_tab[i].type != type)
	{
		if (i == 17)
			break;
		i++;
	}
	return (i);
}

static char	*param_encoding(t_token *param, int	*len)
{
	char	*ret;

	if (!(ret = malloc(sizeof(char) * 5)))
		return (NULL);
	ft_bzero(ret, 5);
	if (param->type == REG)
		ret[0] = ft_atoi(&(param->content[1]));
	if (param->type == DIRECT)
		ret[0] = 42;
	if(param->type == INDIRECT)
		ret[0] = 43;
	len++;
	return (ret);
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

void	add_line(int fd, t_instruction *actual)
{
	char	buff[64];
	int		len;
	int		i;
	int		type;

	ft_bzero(buff, 512);
	i = 0;
	len = 1;
	type = get_type(actual->type);
	buff[0] = g_op_tab[type].opcode;
	if (g_op_tab[type].ocp)
	{
		buff[1] = 0;
		len++;
	}
	while (i < actual->argc)
	{
		buff[len++] = param_encoding(actual->args[i], &len);
		if (g_op_tab[type].ocp)
			buff[1] += ocp(actual->args[i]->type, i);
		i++;
	}
	write(fd, buff, len);
}
