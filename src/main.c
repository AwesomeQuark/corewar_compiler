/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 19:24:21 by conoel            #+#    #+#             */
/*   Updated: 2019/05/07 19:53:19 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(int argc, char **argv)
{
	int		fd;
	char	*file;
	t_token	*head;

	fd = 0;
	if (argc < 2 || ft_strcmp(&(argv[1][ft_strlen(argv[1]) - 2]), ".s") != 0)
	{
		ft_putstr_fd("Usage: ./asm [champion_name].s\n", 2);
		return (-1);
	}
	if (!(fd = open(argv[1], O_RDONLY)))
	{
		ft_putstr_fd("Error: can't read the file\n", 2);
		return (-1);
	}
	file = get_the_file(fd);
	head = lexer(file);
	while (head)
	{
		ft_printf("<%s [%d]> ", head->content, head->type);
		head = head->next;
	}
/*	if (parse(head))
	{
		ft_putstr_fd("Error: parsing error\n", 2);
		return(-1);
	}
	transcribe(head);*/
	return (0);
}