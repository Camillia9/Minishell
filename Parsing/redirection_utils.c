/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:57:00 by camansou          #+#    #+#             */
/*   Updated: 2025/05/25 04:00:39 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_heredoc_redirection_cmd(t_command *cmd, t_token *token,
		t_data *data)
{
	char	*content;
	int		was_in_list;

	if (cmd->heredoc_delim && ft_strcmp(cmd->heredoc_delim, token->value) == 0)
		return (1);
	cleanup_existing_heredoc(cmd);
	was_in_list = manage_command_in_list(cmd, data, 1);
	content = process_heredoc(token->value, data);
	if (!was_in_list)
		manage_command_in_list(cmd, data, 0);
	return (setup_heredoc_content(cmd, content, token->value));
}

int	ft_set_redirection_target(t_command *cmd, t_token *token,
		t_token_type last_redir_type, t_data *data)
{
	if (last_redir_type == REDIR_IN)
	{
		if (cmd->input_file)
			free(cmd->input_file);
		cmd->input_file = ft_strdup(token->value);
	}
	else if (last_redir_type == REDIR_OUT)
	{
		if (cmd->output_file)
			free(cmd->output_file);
		cmd->output_file = ft_strdup(token->value);
	}
	else if (last_redir_type == REDIR_APPEND)
	{
		if (cmd->append_file)
			free(cmd->append_file);
		cmd->append_file = ft_strdup(token->value);
	}
	else if (last_redir_type == HEREDOC)
		return (process_heredoc_redirection_cmd(cmd, token, data));
	return (1);
}

int	handle_new_command_creation(t_token *token, t_parse_ctx *ctx)
{
	*(ctx->current_cmd) = ft_new_command();
	if (!*(ctx->current_cmd))
		return (0);
	(*(ctx->current_cmd))->name_cmd = ft_strdup(token->value);
	return (1);
}
