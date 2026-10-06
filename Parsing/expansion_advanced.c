/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_advanced.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:50:00 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:16:14 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell.h"

static int	ft_handle_quotes_strip(const char *value, int *i, t_quotes *quotes)
{
	if (value[*i] == '\'' && !quotes->in_double)
	{
		quotes->in_single = !quotes->in_single;
		(*i)++;
		return (1);
	}
	else if (value[*i] == '"' && !quotes->in_single)
	{
		quotes->in_double = !quotes->in_double;
		(*i)++;
		return (1);
	}
	return (0);
}

static int	ft_process_variable_strip(const char *value, int *i,
		t_expand_ctx *ctx)
{
	if (value[*i] == '$' && value[*i + 1] && (ft_is_var_char(value[*i + 1])
			|| value[*i + 1] == '?') && !ctx->quotes->in_single)
	{
		if (!ft_process_variable(value, i, ctx->expanded, ctx->data))
		{
			free(*ctx->expanded);
			return (0);
		}
		return (1);
	}
	return (0);
}

static int	ft_process_backslash(const char *value, int *i, char **expanded,
		t_quotes *quotes)
{
	if (value[*i] == '\\' && value[*i + 1] && !quotes->in_single)
	{
		(*i)++;
		if (!ft_process_char(value, i, expanded))
		{
			free(*expanded);
			return (0);
		}
		return (1);
	}
	return (0);
}

static int	ft_process_expand_char(const char *value, int *i, t_expand_ctx *ctx)
{
	if (ft_handle_quotes_strip(value, i, ctx->quotes))
		return (1);
	else if (ft_process_backslash(value, i, ctx->expanded, ctx->quotes))
	{
		if (!*ctx->expanded)
			return (0);
		return (1);
	}
	else if (ft_process_variable_strip(value, i, ctx))
	{
		if (!*ctx->expanded)
			return (0);
		return (1);
	}
	else
	{
		if (!ft_process_char(value, i, ctx->expanded))
		{
			free(*ctx->expanded);
			return (0);
		}
		return (1);
	}
}

char	*ft_expand_and_strip(const char *value, t_data *data)
{
	int				i;
	char			*expanded;
	t_quotes		quotes;
	t_expand_ctx	ctx;

	if (!value)
		return (ft_strdup(""));
	i = 0;
	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	ft_init_quotes(&quotes);
	ctx.expanded = &expanded;
	ctx.data = data;
	ctx.quotes = &quotes;
	while (value[i])
	{
		if (!ft_process_expand_char(value, &i, &ctx))
		{
			if (expanded)
				free(expanded);
			return (NULL);
		}
	}
	return (expanded);
}
