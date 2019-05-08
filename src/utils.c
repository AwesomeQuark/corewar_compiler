#include "asm.h"

int	is_instruction(t_token *token)
{
	t_token_type t;

	t = token->type;
	if (t >= 2 && t <= 13)
		return (1);
	else
		return (0);
}
