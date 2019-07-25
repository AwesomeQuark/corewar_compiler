/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 11:27:46 by conoel            #+#    #+#             */
/*   Updated: 2019/06/24 13:36:32 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

int		compile(t_token *head, char *compiled_file_name)
{
	t_instruction	*code;
	int		fd;

	if (!(fd = open(compiled_file_name , O_CREAT | O_WRONLY | O_TRUNC, 0644)))
		return (return_("Error: failed to compile (compile, compile.c)"));
	header(head, fd);
	head = NULL;
	code = get_instructions(NULL);
	code = code->next;
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
