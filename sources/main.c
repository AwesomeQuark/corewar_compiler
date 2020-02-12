/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 19:24:21 by conoel            #+#    #+#             */
/*   Updated: 2020/02/12 17:30:23 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		*file_name(char *name)
{
	char	*name_s;
	char	*ret;

	name_s = ft_strdup(name);
	name_s[ft_strlen(name_s) - 2] = '\0';
	ret = concat("./", name_s, ".cor");
	free(name_s);
	return (ret);
}

static void		options_arguments(int argc, char **argv,
	char **compiled_file_name, char **assembly_file_name)
{
	int i;

	i = 0;
	while (++i < argc)
	{
		if (ft_strcmp(argv[i], "-dest") == 0 && i + 1 < argc &&
			ft_strcmp(&argv[i + 1][ft_strlen(argv[i + 1]) - 4], ".cor") == 0)
		{
			*compiled_file_name = ft_strdup(argv[++i]);
			continue ;
		}
		if (ft_strcmp(argv[i], "-src") == 0 && i + 1 < argc &&
			ft_strcmp(&argv[i + 1][ft_strlen(argv[i + 1]) - 2], ".s") == 0)
		{
			*assembly_file_name = argv[++i];
			continue ;
		}
	}
}

static int		options(int argc, char **argv, char **compiled_file_name
	, char **assembly_file_name)
{
	*assembly_file_name = NULL;
	*compiled_file_name = NULL;
	if (argc == 2 && ft_strcmp(&argv[1][ft_strlen(argv[1]) - 2], ".s") == 0)
	{
		*assembly_file_name = argv[1];
		*compiled_file_name = file_name(argv[1]);
	}
	options_arguments(argc, argv, compiled_file_name, assembly_file_name);
	return (*assembly_file_name == NULL || *compiled_file_name == NULL ? 0 : 1);
}

static t_token	*get_tokens(char *file_name)
{
	int			fd;
	char		*file;
	t_token		*token_head;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return ((void *)return_("Error: can't read the file"));
	if (!(file = get_the_file(fd)))
	{
		close(fd);
		return ((void *)return_("Error: can't load the file"));
	}
	close(fd);
	if (!(token_head = lexer(file)))
	{
		free(file);
		return ((void *)return_("Error: lexer failure"));
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

int				main(int argc, char **argv)
{
	t_token		*token_head;
	char		*compiled_file_name;
	char		*assembly_file_name;

	if (!options(argc, argv, &compiled_file_name, &assembly_file_name))
		return (return_(USAGE));
	if ((token_head = get_tokens(assembly_file_name)) == NULL)
	{
		return (quit(compiled_file_name, NULL,
			"Error: lexer failure (main, main.c)\n", EXIT_FAILURE));
	}
	if (parse(token_head) == FALSE)
	{
		return (quit(compiled_file_name, token_head,
			"Error: parsing error (main, main.c)\n", EXIT_FAILURE));
	}
	if (compile(token_head, compiled_file_name) == FALSE)
	{
		return (quit(compiled_file_name, token_head,
			"Error: compilation error (main, main.c)\n", EXIT_FAILURE));
	}
	return (quit(compiled_file_name, token_head,
		NULL, EXIT_SUCCESS));
}
