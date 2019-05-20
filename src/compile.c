/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 11:27:46 by conoel            #+#    #+#             */
/*   Updated: 2019/05/20 14:45:44 by conoel           ###   ########.fr       */
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

static void	add_line(int fd, t_instruction *actual)
{
	char	buff[512];
	int		len;
	int		i;
	int		type;

	i = 0;
	len = 1;
	type = get_type(actual->type);
	buff[0] = g_op_tab[type].opcode;
	if (g_op_tab[type].opcode)
	{
		buff[1] = 1;
		len++;
	}
	while (i < actual->argc)
	{
		ft_strcat(&buff[len], param_encoding(actual->args[i++], &len));
	}
	write(fd, buff, len);
}

int		compile(t_token *head, char *file_name_s)
{
	t_instruction	*code;
	int		fd;

	head = NULL;
	code = get_instructions(NULL);
	code = code->next;
	if (!(fd = open(file_name(file_name_s), O_CREAT | O_WRONLY)))
		return (return_("Error: failed to create .cor file (compile, compile.c"));
	while (code)
	{
		add_line(fd, code);
		code = code->next;
	}
	release_instructions();
	return (TRUE);
}