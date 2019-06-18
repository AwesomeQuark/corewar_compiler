/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 11:27:46 by conoel            #+#    #+#             */
/*   Updated: 2019/06/18 22:57:55 by conoel           ###   ########.fr       */
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

static t_magic	tot_prog_size(void)
{
	t_magic			tot;
	t_instruction	*head;

	tot = 0;
	head = get_instructions(NULL);
	while (head)
	{
		tot += head->byte_len;
		head = head->next;
	}
	return (reverse_bits(tot));
}

static void	header(t_token *head, int fd)
{
	header_t	*header;

	if (!(header = malloc(sizeof(header_t))))
		return ;
	ft_bzero(header, sizeof(header_t));
	header->magic = reverse_bits(COREWAR_EXEC_MAGIC);
	next_token(&head);
	ft_strcpy(header->prog_name, head->content);
	next_token(&head);
	ft_strcpy(header->comment, head->content);
	header->prog_size = tot_prog_size();
	write(fd, header, sizeof(header_t));
	free (header);
}

int		compile(t_token *head, char *file_name_s)
{
	t_instruction	*code;
	int		fd;
	char	*tmp;

	tmp = file_name(file_name_s);
	if (!(fd = open(tmp , O_CREAT | O_WRONLY | O_TRUNC, 0644)))
		return (return_("Error: failed to create .cor file (compile, compile.c)"));
	header(head, fd);
	head = NULL;
	code = get_instructions(NULL);
	code = code->next;
	free(tmp);
	while (code)
	{
		if (code->type != LABEL)
			if (!(add_line(fd, code)))
				return (return_("/!\\ Compilation failure /!\\"));
		code = code->next;
	}
	release_instructions();
	return (TRUE);
}
