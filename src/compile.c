/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 11:27:46 by conoel            #+#    #+#             */
/*   Updated: 2019/05/20 19:00:00 by conoel           ###   ########.fr       */
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

static void	add_line(int fd, t_instruction *actual)
{
	char	buff[512];
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
		param_encoding(actual->args[i], &len);
		if (g_op_tab[type].ocp)
			buff[1] += ocp(actual->args[i]->type, i);
		i++;
	}
	write(fd, buff, len);
}

static void	header(t_token *head, int fd)
{
	header_t	*header;

	if (!(header = malloc(sizeof( header_t))))
		return ;
	ft_bzero(header, sizeof(header_t));
	header->magic = COREWAR_EXEC_MAGIC;
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