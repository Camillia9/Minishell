/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:16:14 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_create_word_token(char *word, t_quotes *quotes)
{
	t_quotes	temp_quotes;
	t_token		*token;
	int			len;
	int			is_quoted[2];

	ft_init_quotes(&temp_quotes);
	is_quoted[0] = 0;
	is_quoted[1] = 0;
	len = ft_strlen(word);
	ft_check_quote_types(word, len, is_quoted);
	token = ft_new_token(word, WORD, is_quoted[0] || quotes->in_single,
			is_quoted[1] || quotes->in_double);
	return (token);
}

void	ft_add_word_token(t_token **tokens, const char *start, int len,
		t_quotes *quotes)
{
	char	*word;
	t_token	*new_token;

	word = ft_strndup(start, len);
	if (!word)
		return ;
	new_token = ft_create_word_token(word, quotes);
	if (new_token)
		ft_add_token(tokens, new_token);
	free(word);
}
