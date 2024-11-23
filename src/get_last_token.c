#include "../inc/minishell.h"

static t_list	*find_last(t_list *current, t_list *first)
{
	t_list	*last_cmd;

	last_cmd = NULL;
	while (current)
	{
		if (((t_token *)current->content)->type == TOKEN_TEXT)
			last_cmd = current;
		while (((t_token *)current->content)->type == TOKEN_TEXT)
			current = current->next;
		if (last_cmd && (((t_token *)current->content)->type == TOKEN_END
				|| ((t_token *)current->content)->type == TOKEN_R_OUTPUT
				|| ((t_token *)current->content)->type == TOKEN_A_OUTPUT))
		{
			((t_token *)last_cmd->content)->type = TOKEN_LAST;
			return (first);
		}
		current = current->next;
	}
	return (first);
}

t_list	*finish_tokenizing(t_list *first)
{
	t_list	*current;

	current = first;
	while (((t_token *)current->content)->type == TOKEN_R_INPUT
		|| ((t_token *)current->content)->type == TOKEN_HERE_DOC)
	{
		current = current->next;
		if (current)
			current = current->next;
	}
	find_last(current, first);
	return (first);
}