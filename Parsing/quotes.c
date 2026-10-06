/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:03:06 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_quotes_state(const char *line, int *i, t_quotes *quotes)
{
	if (line[*i] == '\'' && !quotes->in_double)
	{
		quotes->in_single = !quotes->in_single;
		quotes->has_single = 1;
	}
	else if (line[*i] == '"' && !quotes->in_single)
	{
		quotes->in_double = !quotes->in_double;
		quotes->has_double = 1;
	}
	(*i)++;
}

void	ft_check_quote_types(char *word, int len, int is_quoted[2])
{
	if (len >= 2)
	{
		if (word[0] == '\'' && word[len - 1] == '\'')
			is_quoted[0] = ft_check_matching_quotes(word, len, '\'');
		if (word[0] == '"' && word[len - 1] == '"')
			is_quoted[1] = ft_check_matching_quotes(word, len, '"');
	}
}

int	ft_check_matching_quotes(char *word, int len, char quote_type)
{
	int	i;

	i = 0;
	while (++i < len - 1)
		if (word[i] == quote_type)
			return (0);
	return (1);
}
