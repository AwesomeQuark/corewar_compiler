/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 11:27:46 by conoel            #+#    #+#             */
/*   Updated: 2019/05/23 16:55:22 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*file_name(char *name_s)
{
	char	*ret;

	name_s[ft_strlen(name_s) - 2] = '\0';
	ret = concat("./", name_s, ".cor");
	return (ret);
}

static t_magic	reverse_bits(t_magic magic)
{
	int		i;
	t_magic tmp;

	tmp = 0;
	i = sizeof(t_magic);
	while (i > 0)
	{
		printf("%x\n", magic);
		tmp = tmp >> 8;
		tmp += magic << 8;
		magic = magic << 8;
		i--;
	}
	return (tmp);
}

static void	header(t_token *head, int fd)
{
	header_t	*header;

	if (!(header = malloc(sizeof( header_t))))
		return ;
	ft_bzero(header, sizeof(header_t));
	header->magic = reverse_bits(COREWAR_EXEC_MAGIC);
	next_token(&head);
	ft_strcpy(header->prog_name, head->content);
	next_token(&head);
	ft_strcpy(header->comment, head->content);
	write(fd, header, sizeof(header_t));
}

int		compile(t_token *head, char *file_name_s)
{
	t_instruction	*code;
	int		fd;
	char	*tmp;

	tmp = file_name(file_name_s);
	if (!(fd = open(tmp , O_CREAT | O_WRONLY | O_TRUNC, 0644)))
		return (return_("Error: failed to create .cor file (compile, compile.c"));
	header(head, fd);
	head = NULL;
	code = get_instructions(NULL);
	code = code->next;
	tmp = file_name(file_name_s);
	free(tmp);
	while (code)
	{
		add_line(fd, code);
		code = code->next;
	}
	release_instructions();
	return (TRUE);
}
