/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/25 03:44:32 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_word_token(t_token *token, t_parse_ctx *ctx, t_data *data)
{
	if (ctx->expecting_target)
	{
		ft_set_redirection_target(*(ctx->current_cmd), token,
			ctx->last_redir_type, data);
		ctx->expecting_target = 0;
	}
	else
	{
		if (!*(ctx->current_cmd))
		{
			if (!handle_new_command_creation(token, ctx))
				return (0);
		}
		if (*(ctx->current_cmd))
			ft_add_arg(*(ctx->current_cmd), token->value);
	}
	return (1);
}

int	handle_pipe_token(t_command **current_cmd, t_data *data)
{
	if (*current_cmd)
	{
		ft_add_command(data, *current_cmd);
		*current_cmd = NULL;
	}
	return (1);
}

int	handle_redirection_token(t_parse_state *state, t_token *current)
{
	if (current->type == REDIR_IN || current->type == REDIR_OUT
		|| current->type == REDIR_APPEND || current->type == HEREDOC)
	{
		if (!*(state->current_cmd))
		{
			*(state->current_cmd) = ft_new_command();
			if (!*(state->current_cmd))
			{
				ft_free_commands(state->data);
				return (0);
			}
		}
		*(state->expecting_target) = 1;
		*(state->last_type) = current->type;
	}
	return (1);
}

int	handle_word_token_main(t_parse_state *state, t_token *current)
{
	t_parse_ctx	ctx;

	ctx.current_cmd = state->current_cmd;
	ctx.expecting_target = *(state->expecting_target);
	ctx.last_redir_type = *(state->last_type);
	if (!ft_process_token(current, &ctx, state->data))
	{
		ft_free_commands(state->data);
		return (0);
	}
	*(state->expecting_target) = ctx.expecting_target;
	return (1);
}

int	process_single_token(t_token *current, t_parse_state *state)
{
	if (current->type == PIPE)
		handle_pipe_token(state->current_cmd, state->data);
	else if (current->type != WORD && current->type != PIPE)
	{
		if (!handle_redirection_token(state, current))
			return (0);
	}
	else
	{
		if (!handle_word_token_main(state, current))
			return (0);
	}
	return (1);
}
