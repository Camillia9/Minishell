/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:03:06 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strip_quotes(const char *str, t_quotes *quotes)
{
	ft_init_quotes(quotes);
	return (ft_process_quotes(str, quotes));
}

char	*ft_process_quotes(const char *str, t_quotes *quotes)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' && !quotes->in_double)
			ft_handle_quotes(str, &i, quotes, '\'');
		else if (str[i] == '"' && !quotes->in_single)
			ft_handle_quotes(str, &i, quotes, '"');
		else
			ft_copy_char(str, &i, result, &j);
	}
	result[j] = '\0';
	return (result);
}

void	ft_handle_quotes(const char *str, int *i, t_quotes *quotes,
		char quote_type)
{
	(void)str;
	if (quote_type == '\'')
	{
		quotes->in_single = !quotes->in_single;
		quotes->has_single = 1;
	}
	else if (quote_type == '"')
	{
		quotes->in_double = !quotes->in_double;
		quotes->has_double = 1;
	}
	(*i)++;
}
