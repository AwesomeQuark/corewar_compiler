/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 20:07:06 by conoel            #+#    #+#             */
/*   Updated: 2019/06/05 22:42:32 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_size(int n)
{
	int size;

	size = 0;
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size + 1);
}

char			*ft_itoa_base(int n, int base)
{
	char	*end;
	int		size;

	size = ft_size(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (!(end = (char *)malloc(sizeof(char) * size--)))
		return (0);
	end[size--] = '\0';
	if (n < 0)
	{
		end[0] = '-';
		n *= -1;
	}
	if (n == 0)
		end[0] = 48;
	while (n)
	{
		end[size--] = (n < 10 ? n % base + '0' : n % base + 'A');
		n = n / base;
	}
	return (end);
}
