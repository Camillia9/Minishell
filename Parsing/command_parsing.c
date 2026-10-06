/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/25 03:44:00 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_redirection_target(t_token *token, int *expecting_redir_target,
		t_token_type *last_redir_type)
{
	*expecting_redir_target = 1;
	*last_redir_type = token->type;
	return (1);
}

void	ft_init_parsing(t_data *data, t_command **current_cmd,
		int *expecting_target, t_token_type *last_type)
{
	*current_cmd = NULL;
	*expecting_target = 0;
	*last_type = WORD;
	data->cmd_count = 0;
}

int	ft_handle_pipe(t_data *data, t_command **current_cmd)
{
	if (*current_cmd)
	{
		ft_add_command(data, *current_cmd);
		*current_cmd = NULL;
	}
	return (1);
}

int	ft_process_token(t_token *token, t_parse_ctx *ctx, t_data *data)
{
	if (token->type == PIPE)
		return (1);
	if (token->type == WORD)
		ft_handle_word_token(token, ctx, data);
	return (1);
}

int	finalize_last_command(t_command *current_cmd, t_data *data)
{
	if (current_cmd)
	{
		ft_add_command(data, current_cmd);
	}
	return (1);
}
