/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:41:16 by conoel            #+#    #+#             */
/*   Updated: 2019/03/19 16:56:20 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*end;
	size_t		index;

	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	index = 0;
	if (!(end = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (*s1)
		end[index++] = *(s1++);
	while (*s2)
		end[index++] = *(s2++);
	end[index] = '\0';
	return (end);
}
