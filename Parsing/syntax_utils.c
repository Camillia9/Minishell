/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:16:14 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_syntax_start(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (tokens->type == PIPE)
	{
		ft_putstr_fd(" syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	return (1);
}

int	ft_check_redir_syntax(t_token *token, int *expecting_word)
{
	if (*expecting_word)
	{
		if (token->type != WORD)
		{
			ft_syntax_token_error(token->type);
			return (0);
		}
		*expecting_word = 0;
	}
	else if (ft_is_redirection(token->type))
		*expecting_word = 1;
	return (1);
}

int	ft_check_pipe_syntax(t_token *token, int *cmd_present)
{
	if (!*cmd_present)
	{
		ft_putstr_fd(" syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	if (!token->next)
	{
		ft_putstr_fd("syntax error: unexpected end of file\n", 2);
		return (0);
	}
	if (token->next->type == PIPE)
	{
		ft_putstr_fd(" syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	*cmd_present = 0;
	return (1);
}

int	ft_check_pipe_redir(t_token *current)
{
	t_token	*redir;

	if (current->type == PIPE && current->next
		&& ft_is_redirection(current->next->type))
	{
		redir = current->next;
		if (!redir->next || redir->next->type != WORD)
		{
			ft_syntax_token_error(redir->type);
			return (0);
		}
	}
	return (1);
}
