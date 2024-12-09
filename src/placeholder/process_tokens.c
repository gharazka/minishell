/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gharazka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:23:45 by gharazka          #+#    #+#             */
/*   Updated: 2024/08/21 21:23:46 by gharazka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	process_tokens(t_list *tokens, char *envp[], t_data *data)
{
	t_list	*to_free;

	while (((t_token *)tokens->content)->type != TOKEN_END)
	{
		if (((t_token *)tokens->content)->type == TOKEN_TEXT
			|| ((t_token *)tokens->content)->type == TOKEN_LAST)
			handle_token_exec(&tokens, &data);
		else if (((t_token *)tokens->content)->type == TOKEN_PIPE)
			handle_token_pipe(&tokens, &data);
		else if (((t_token *)tokens->content)->type == TOKEN_R_INPUT)
			handle_token_input(&tokens);
		else if (((t_token *)tokens->content)->type == TOKEN_HERE_DOC)
			handle_token_here_doc(&tokens);
		else if (((t_token *)tokens->content)->type == TOKEN_R_OUTPUT
			|| ((t_token *)tokens->content)->type == TOKEN_A_OUTPUT)
			handle_token_output(&tokens);
	}
	while (data->ids)
	{
		waitpid((__pid_t)(intptr_t)data->ids->content, NULL, 0);
		to_free = data->ids;
		data->ids = data->ids->next;
		free(to_free);
	}
	g_sigint_received = 0;
}

// void	process_tokens(t_list *tokens, char *envp[], t_data *data)
// {
// 	t_list	*to_free;

// 	while (((t_token *)tokens->content)->type != TOKEN_END)
// 	{
// 		if (((t_token *)tokens->content)->type == TOKEN_TEXT
// 			|| ((t_token *)tokens->content)->type == TOKEN_LAST)
// 		{
// 			data = process_exec(&tokens, &((t_token *)tokens->content)->type,
// 					data);
// 		}
// 		else if (((t_token *)tokens->content)->type == TOKEN_PIPE)
// 		{
// 			tokens = tokens->next;
// 			data = process_exec(&tokens, &((t_token *)tokens->content)->type,
// 					data);
// 		}
// 		else if (((t_token *)tokens->content)->type == TOKEN_R_INPUT)
// 		{
// 			if (redirect_input(((t_token *)tokens->next->content)->value) == -1)
// 				break ;
// 			tokens = tokens->next->next;
// 		}
// 		else if (((t_token *)tokens->content)->type == TOKEN_HERE_DOC)
// 		{
// 			here_doc(((t_token *)tokens->next->content)->value);
// 			tokens = tokens->next->next;
// 		}
// 		else if (((t_token *)tokens->content)->type == TOKEN_R_OUTPUT
// 			|| (((t_token *)tokens->content)->type == TOKEN_A_OUTPUT))
// 		{
// 			redirect_output(((t_token *)tokens->next->content)->value,
// 				((t_token *)tokens->content)->type, 0);
// 			tokens = tokens->next->next;
// 		}
// 	}
// 	while (data->ids)
// 	{
// 		waitpid((__pid_t)(intptr_t)data->ids->content, NULL, 0);
// 		to_free = data->ids;
// 		data->ids = data->ids->next;
// 		free(to_free);
// 	}
// 	g_sigint_received = 0;
// }
