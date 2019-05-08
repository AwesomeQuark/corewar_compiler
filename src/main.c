/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 19:24:21 by conoel            #+#    #+#             */
/*   Updated: 2019/05/08 18:08:14 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_ast_node	*get_ast(char *file_name)
{
	int			fd;
	char		*file;
	t_token		*token_head;
	t_ast_node	*instructions;

	if (!(fd = open(file_name, O_RDONLY)))
		return ((void *)return_("Error: can't read the file (get_ast, main.c)"));
	if (!(file = get_the_file(fd)))
	{
		close(fd);
		return ((void *)return_("Error: can't load the file (get_ast, main.c)"));
	}
	close(fd);
	if (!(token_head = lexer(file)))
	{
		free(file);
		return ((void *)return_("Error: lexer failure (get_ast, main.c)"));
	}
	free(file);
	/*if (!(instructions = build_ast(token_head)))
	{
		release_tokens(token_head);
		return ((void *)return_("Error: ast build failure (get_ast, main.c)"));
	}
	release_tokens(token_head);*/
	//return (instructions);
	print_tokens(token_head);
	return (NULL);
}

int		main(int argc, char **argv)
{
	t_ast_node	*instructions;

	if (argc < 2 || ft_strcmp(&(argv[1][ft_strlen(argv[1]) - 2]), ".s") != 0)
	{
		ft_putstr_fd("Usage: ./asm [champion_name].s\n", 2);
		return (EXIT_FAILURE);
	}
	if ((instructions = get_ast(argv[1])) == NULL)
	{
		ft_putstr_fd("Error: cannot build AST (main, main.c)\n", 2);
		return (EXIT_FAILURE);
	}
/*	if (parse(instructions) == FALSE)
	{
		ft_putstr_fd("Error: parsing error (main, main.c)\n", 2);
		return(EXIT_FAILURE);
	}
	if (transcribe(instructions) == FALSE)
	{
		ft_putstr_fd("Error: compilation failure (main, main.c)\n", 2);
		return (EXIT_FAILURE);
	}*/
	return (EXIT_SUCCESS);
}