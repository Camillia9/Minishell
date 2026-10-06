/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:03:06 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_and_parse(t_data *data, const char *line)
{
	data->tokens = ft_lexer(line);
	ft_expand_tokens(data);
	if (!ft_check_syntax(data->tokens))
	{
		ft_free_tokens(data->tokens);
		data->tokens = NULL;
		return (0);
	}
	if (!ft_parse_commands(data))
	{
		ft_free_tokens(data->tokens);
		data->tokens = NULL;
		return (0);
	}
	return (1);
}

int	check_pipe_token(t_token *current, int *cmd_present)
{
	if (!ft_check_pipe_syntax(current, cmd_present)
		|| !ft_check_pipe_redir(current))
		return (0);
	return (1);
}

int	check_token_syntax(t_token *current, int *expecting_word, int *cmd_present)
{
	if (!ft_check_redir_syntax(current, expecting_word))
		return (0);
	if (current->type == PIPE)
	{
		if (!check_pipe_token(current, cmd_present))
			return (0);
	}
	else if (current->type == WORD)
		*cmd_present = 1;
	return (1);
}

int	ft_check_syntax(t_token *tokens)
{
	t_token	*current;
	int		expecting_word;
	int		cmd_present;

	if (!ft_check_syntax_start(tokens))
		return (0);
	current = tokens;
	expecting_word = 0;
	cmd_present = 0;
	while (current)
	{
		if (!check_token_syntax(current, &expecting_word, &cmd_present))
			return (0);
		current = current->next;
	}
	if (expecting_word)
		return (ft_putstr_fd("syntax error: missing redirection target\n", 2),
			0);
	return (1);
}

void	ft_syntax_token_error(t_token_type type)
{
	ft_putstr_fd(" syntax error near unexpected token `", 2);
	if (type == PIPE)
		ft_putstr_fd("|'\n", 2);
	else if (type == REDIR_IN)
		ft_putstr_fd("<'\n", 2);
	else if (type == REDIR_OUT)
		ft_putstr_fd(">'\n", 2);
	else if (type == REDIR_APPEND)
		ft_putstr_fd(">>'\n", 2);
	else if (type == HEREDOC)
		ft_putstr_fd("<<'\n", 2);
}
