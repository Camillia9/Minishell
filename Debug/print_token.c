/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 16:44:49 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Affichage des tokens */
char	*ft_get_token_type_str(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIR_IN)
		return ("REDIR_IN");
	if (type == REDIR_OUT)
		return ("REDIR_OUT");
	if (type == REDIR_APPEND)
		return ("APPEND");
	if (type == HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

void	ft_print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("TYPE: %-12s | VALUE: %-15s | SQ: %d | DQ: %d\n",
			ft_get_token_type_str(tokens->type), tokens->value,
			tokens->quoted_single, tokens->quoted_double);
		tokens = tokens->next;
	}
}
