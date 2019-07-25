/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 19:24:21 by conoel            #+#    #+#             */
/*   Updated: 2019/06/24 17:00:56 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*file_name(char *name)
{
	char	*name_s;
	char	*ret;

	name_s = ft_strdup(name);
	name_s[ft_strlen(name_s) - 2] = '\0';
	ret = concat("./", name_s, ".cor");
	free(name_s);
	return (ret);
}

static int		options(int argc, char **argv, char **compiled_file_name
	, char **assembly_file_name)
{
	int		i;

	i = 0;
	*assembly_file_name = NULL;
	*compiled_file_name = NULL;
	if (argc == 2 && ft_strcmp(&argv[1][ft_strlen(argv[1]) - 2], ".s") == 0)
	{
		*assembly_file_name = argv[1];
		*compiled_file_name = file_name(argv[1]);
	}
	while (++i < argc)
	{
		if (ft_strcmp(argv[i], "-dest") == 0 && i + 1 < argc && ft_strcmp(&argv[i + 1][ft_strlen(argv[i + 1]) - 4], ".cor") == 0)
		{
			*compiled_file_name = argv[++i];
			continue ;
		}
		if (ft_strcmp(argv[i], "-src") == 0 && i + 1 < argc && ft_strcmp(&argv[i + 1][ft_strlen(argv[i + 1]) - 2], ".s") == 0)
		{
			*assembly_file_name = argv[++i];
			continue ;
		}
	}
	if (*assembly_file_name == NULL || *compiled_file_name == NULL)
		return (0);
	return (1);
}

static t_token	*get_tokens(char *file_name)
{
	int			fd;
	char		*file;
	t_token		*token_head;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return ((void *)return_("Error: can't read the file \
			(get_tokens, main.c)"));
	if (!(file = get_the_file(fd)))
	{
		close(fd);
		return ((void *)return_("Error: can't load the file \
			(get_tokens, main.c)"));
	}
	close(fd);
	if (!(token_head = lexer(file)))
	{
		free(file);
		return ((void *)return_("Error: lexer failure (get_tokens, main.c)"));
	}
	free(file);
	print_tokens(token_head);
	return (token_head);
}

/*
**	1) Remplissage des tokens avec "get_tokens()"
**	2) Construction de l'AST t_instruction avec singletone dans "parse()"
**	3) Compilation et ecriture du bytecode dans "compile()"
*/

int			main(int argc, char **argv)
{
	t_token		*token_head;
	char		*compiled_file_name;
	char		*assembly_file_name;

	if (!options(argc, argv, &compiled_file_name, &assembly_file_name))
		return (return_("Usage:\t./asm [champion_name].s\n\t./asm -src [champion_name].s -dest [compiled_file].cor"));
	if ((token_head = get_tokens(assembly_file_name)) == NULL)
	{
		ft_putstr_fd("Error: lexer failure (main, main.c)\n", 2);
		return (EXIT_FAILURE);
	}
	if (parse(token_head) == FALSE)
	{
		release_tokens(token_head);
		ft_putstr_fd("Error: parsing error (main, main.c)\n", 2);
		return (EXIT_FAILURE);
	}
	if (compile(token_head, compiled_file_name) == FALSE)
	{
		release_tokens(token_head);
		ft_putstr_fd("Error: compilation error (main, main.c)\n", 2);
		return (EXIT_FAILURE);
	}
	release_tokens(token_head);
	return (EXIT_SUCCESS);
}
