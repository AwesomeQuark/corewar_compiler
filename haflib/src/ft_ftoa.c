/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 12:34:16 by conoel            #+#    #+#             */
/*   Updated: 2019/05/25 12:58:05 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			get_size(long long nb, t_flag *all)
{
	int size;
	int prec;

	prec = all->precision;
	size = 0;
	all->plus && nb >= 0 ? size++ : 0;
	all->space && nb >= 0 ? size++ : 0;
	prec == 1 && nb != 0 ? size-- : 0;
	if (nb < 0)
	{
		size++;
		nb *= -1;
	}
	if (nb == 0)
		size += prec - 2;
	while (nb > 0)
	{
		size += 1;
		nb /= 10;
	}
	return (size);
}

static long long	pow(long double num, int pow)
{
	while (pow-- > 0)
		num *= 10;
	if (num > 0)
		(long)num % 10 >= 5 ? num += 10 : 0;
	else
		((long)num * -1) % 10 >= 5 ? num -= 10 : 0;
	num /= 10;
	return ((long long)num);
}

static void			if_nbzero(char *tmp, t_flag *all, int *size)
{
	int	prec;

	prec = all->precision;
	while (prec-- > 1)
		tmp[--(*size)] = '0';
	tmp[--(*size)] = '.';
	tmp[--(*size)] = '0';
}

static void			printer(t_flag *all, long long nb, int size, int p_i)
{
	char		tmp[50];
	int			minsize;
	long long	nb_mem;

	nb_mem = nb;
	ft_bzero(tmp, 50);
	minsize = all->minsize - get_size(nb, all);
	while (all->minus && minsize-- > 1)
		tmp[--size] = all->zero ? '0' : ' ';
	if (nb < 0)
		nb *= -1;
	nb == 0 ? if_nbzero(tmp, all, &size) : 0;
	while (nb > 0)
	{
		size == p_i && all->precision != 1 ? tmp[--size] = '.' : 0;
		size + 1 == p_i ? p_i = 0 : 0;
		tmp[--size] = nb % 10 + 48;
		nb /= 10;
	}
	all->plus && nb_mem >= 0 ? tmp[--size] = '+' : 0;
	nb_mem < 0 ? tmp[--size] = '-' : 0;
	while (!all->minus && minsize-- > 0)
		tmp[--size] = all->zero ? '0' : ' ';
	all->space && nb_mem >= 0 ? tmp[--size] = ' ' : 0;
	ft_strcat2(tmp, all);
}

void				ft_ftoa(long double num, t_flag *all)
{
	long long	nb;
	int			size;
	int			point_i;

	all->precision = all->precision == -1 ? 7 : all->precision + 1;
	nb = pow(num, all->precision);
	size = get_size(nb, all);
	point_i = get_size(num, all);
	point_i += all->minsize > size && all->minus == 0 ? all->minsize - size : 1;
	nb == 0 ? point_i = 2 : 0;
	size = size > all->minsize ? size + 1 : all->minsize;
	if (all->precision != 1)
		printer(all, nb, size, point_i);
	else
		printer(all, nb, get_size(nb, all) + 1, point_i);
}
