/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 13:49:22 by conoel            #+#    #+#             */
/*   Updated: 2019/06/05 22:50:40 by conoel           ###   ########.fr       */
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

int		ft_natoi_hex(char *nb, int n)
{
	int	i;
	int	tot;
	int	signe;

	tot = 0;
	i = 0;
	if (nb[0] == '-')
	{
		i++;
		signe = -1;
	}
	else
		signe = 1;
	while (nb[i] && i < n)
	{
		tot *= 16;
		tot += (ft_isdigit(nb[i]) ? (nb[i] - '0') : (nb[i] - 'A'));
		i++;
	}
	return (tot);
}

void		str_to_direct_param(char *param, int *len, char *str)
{
	int		nb;
	char	*nb_hex;
	int		nb_len;
	int		i;

	i = 0;
	nb = ft_atoi(param);
	nb_hex = ft_itoa_base(nb, 16);
	nb_len = ft_strlen(nb_hex) / 2 + ft_strlen(nb_hex) % 2;
	while (nb_len--)
	{
		str[*len] = 0;
		*len += 1;
	}
	while (nb_hex[i] && i < 8)
	{
		str[*len] = ft_natoi_hex(nb_hex, 2);
		i += 2;
		*len += 1;
	}
}

static void	param_encoding(t_token *param, int *len, char *str)
{
	if (param->type == REG)
	{
		str[*len] = param->content[1] - '0';
		*len += 1;
	}
	if (param->type == DIRECT)  //TODO
	{
		str_to_direct_param(param->content, len, str);
	}
	if(param->type == INDIRECT) //TODO
	{
		str[*len] = 42;
		*len += 1;
	}
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
	ft_bzero(buff, 64);
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
		param_encoding(actual->args[i], &len, buff);
		if (g_op_tab[type].ocp)
			buff[1] += ocp(actual->args[i]->type, i);
		i++;
		
	}
	return (write(fd, buff, len));
}
