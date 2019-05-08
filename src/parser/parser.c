#include "asm.h"

int	parse(t_token *head)
{
	while (head)
	{
		if (head->type == LABEL && (!is_instruction(head->next)|| head->next->type == EOF_))
			ft_printf("Warning: syntax error (%s) [line ]", head->next->content);
		head = head->next;
	}
	return (1);
}
