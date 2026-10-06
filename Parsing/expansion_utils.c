/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:16:14 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell.h"

char	*ft_extract_varname(const char *value, int *i)
{
	int		start;
	char	*name;
	int		len;

	(*i)++;
	start = *i;
	while (value[*i] && ft_is_var_char(value[*i]))
		(*i)++;
	len = *i - start;
	name = malloc(len + 1);
	if (!name)
		return (NULL);
	ft_strncpy(name, &value[start], len);
	name[len] = '\0';
	return (name);
}

char	*handle_null_inputs(char *s1, char *s2, int free_s2)
{
	if (!s2)
		return (s1);
	if (!s1)
	{
		if (free_s2)
			return (s2);
		else
			return (ft_strdup(s2));
	}
	return (NULL);
}

char	*create_joined_result(char *s1, char *s2, int free_s2)
{
	char	*result;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(len + 1);
	if (!result)
	{
		if (free_s2)
			free(s2);
		return (NULL);
	}
	ft_strcpy(result, s1);
	ft_strcat(result, s2);
	free(s1);
	if (free_s2)
		free(s2);
	return (result);
}

char	*ft_join_strings(char *s1, char *s2, int free_s2)
{
	char	*null_check;

	null_check = handle_null_inputs(s1, s2, free_s2);
	if (null_check != NULL)
		return (null_check);
	return (create_joined_result(s1, s2, free_s2));
}

void	ft_expand_tokens(t_data *data)
{
	t_token	*token;
	char	*expanded;
	char	*tilde_expanded;

	token = data->tokens;
	while (token)
	{
		if (token->type == WORD)
		{
			tilde_expanded = ft_expand_tilde(token->value, data);
			if (tilde_expanded)
			{
				expanded = ft_expand_and_strip(tilde_expanded, data);
				if (expanded)
				{
					free(token->value);
					token->value = expanded;
				}
				free(tilde_expanded);
			}
		}
		token = token->next;
	}
}
