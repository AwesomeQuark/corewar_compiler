#include "asm.h"

int	is_instruction(t_token *token)
{
	t_token_type t;

	t = token->type;
	if (t >= LIVE && t <= AFF)
		return (1);
	else
		return (0);
}

int	is_parameter(t_token *token)
{
	t_token_type t;

	t = token->type;
	if (t == DIRECT || t == REG || t == STRING)
		return (1);
	else
		return (0);
}
