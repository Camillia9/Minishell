/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilities.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:28:29 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (true);
	return (false);
}

int	ft_is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	ft_is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/* Vérifie si un token est une redirection */
int	ft_is_redirection(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT || type == REDIR_APPEND
		|| type == HEREDOC);
}
