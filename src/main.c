/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 19:24:21 by conoel            #+#    #+#             */
/*   Updated: 2019/05/20 19:26:32 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_token *get_tokens(char *file_name)
{
	int			fd;
	char		*file;
	t_token		*token_head;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return ((void *)return_("Error: can't read the file (get_tokens, main.c)"));
	if (!(file = get_the_file(fd)))
	{
		close(fd);
		return ((void *)return_("Error: can't load the file (get_tokens, main.c)"));
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

int		main(int argc, char **argv)
{
	t_token		*token_head;

	if (argc < 2 || ft_strcmp(&(argv[1][ft_strlen(argv[1]) - 2]), ".s") != 0)
	{
		ft_putstr_fd("Usage: ./asm [champion_name].s\n", 2);
		return (EXIT_FAILURE);
	}
	if ((token_head = get_tokens(argv[1])) == NULL)
	{
		ft_putstr_fd("Error: cannot parse the file (main, main.c)\n", 2);
		return (EXIT_FAILURE);
	}
	if (parse(token_head) == FALSE)
	{
		release_tokens(token_head);
		ft_putstr_fd("Error: parsing error (main, main.c)\n", 2);
		return(EXIT_FAILURE);
	}
	if (compile(token_head, argv[1]) == FALSE)
	{
		release_tokens(token_head);
		ft_putstr_fd("Error: compilation error (main, main.c)\n", 2);
		return(EXIT_FAILURE);
	}
	release_tokens(token_head);
	return (EXIT_SUCCESS);
}
