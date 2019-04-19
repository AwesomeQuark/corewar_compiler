/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:52:03 by conoel            #+#    #+#             */
/*   Updated: 2019/04/10 15:34:31 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token_def	tokens[] =
{
	{"{", 1, OPENING_BRACE},
	{"}", 1, CLOSING_BRACE},
	{"(", 1, OPENING_PARENTHESE},
	{")", 1, CLOSING_PARENTHESE},
	{"[", 1, OPENING_BRACKET},
	{"]", 1, CLOSING_BRACKET},
	{"+", 1, PLUS},
	{"-", 1, MINUS},
	{"/", 1, DIVIDE},
	{"*", 1, MULTIPLY},
	{"jood", 4, JEW},
	{"AnneFrank", 9, PRINT},
	{"optellen", 8, ADD},
	{NULL, 0, STOP}
};

static int		handle_escape(char **file)
{
	if (**file == ' ' || **file == '\t' || **file == '\n')
		return (1);
	if (ft_strncmp(*file, "\\*", 2) == 0)
	{
		while (*file && ft_strncmp(*file, "*\\", 2) != 0)
			(*file) += 1;
		return (1);
	}
	if (ft_strncmp(*file, "\"", 1) == 0)
	{
		(*file) += 1;
		while (*file && ft_strncmp(*file, "\"", 2) != 0)
			(*file) += 1;
		return (1);
	}
	if (ft_strncmp(*file, "\'", 1) == 0)
	{
		(*file) += 1;
		while (*file && ft_strncmp(*file, "\'", 2) != 0)
			(*file) += 1;
		return (1);
	}
	return (0);
}

static t_token_def	*search_token_type(char *file)
{
	size_t	i;

	i = 0;
	while (tokens[i].type != STOP)
	{
		if (ft_strncmp(file, tokens[i].content, tokens[i].size) == 0)
			return (&tokens[i]);
		i++;
	}
	return (NULL);
}

int				lexer_main_loop(char *file, t_token *head)
{
	t_token_def	*current;
	char		*last_token_found;

	last_token_found = file;
	while (file && *file)
	{
		if (handle_escape(&file))
		{
			if (last_token_found != file && head->next != NULL)
				add_token(last_token_found, file - last_token_found, misc_type(last_token_found, file - last_token_found), head);
			file++;
			last_token_found = file;
			continue ;
		}
		if (!(current = search_token_type(file)))
		{
			file++;
			continue ;
		}
		if (last_token_found != file && head->next != NULL)
			add_token(last_token_found, file - last_token_found, misc_type(last_token_found, file - last_token_found), head);
		file += current->size;
		last_token_found = file;
		if (!(add_token(current->content, current->size, current->type, head)))
			return (0);
	}
	if (last_token_found != file && head->next != NULL)
		add_token(last_token_found, file - last_token_found, misc_type(last_token_found, file - last_token_found), head);
	return (1);
}

t_token			*lexer(int fd)
{
	t_token	*head;
	char	*file;
	size_t	i;

	if (fd < 0)
		return (NULL);
	i = 0;
	if (!(file = get_the_file(fd)))
		return ((t_token *)malloc_garbage(0));
	if (!(head = malloc_garbage(sizeof(t_token))))
		return (NULL);
	head->type = START;
	head->next = NULL;
	head->size = 0;
	head->content = NULL;
	lexer_main_loop(file, head);
	return (head);
}