/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:50:00 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:16:14 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell.h"

static int	ft_process_double_quote_exp(const char *value, int *i,
		t_expand_ctx *ctx)
{
	if (value[*i] == '"' && !ctx->quotes->in_single)
	{
		ctx->quotes->in_double = !ctx->quotes->in_double;
		if (!ft_process_char(value, i, ctx->expanded))
		{
			free(*ctx->expanded);
			return (0);
		}
		return (1);
	}
	return (-1);
}

static int	ft_process_variable_exp(const char *value, int *i,
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
	return (-1);
}

static int	ft_process_single_quote_exp(const char *value, int *i,
		t_expand_ctx *ctx)
{
	if (value[*i] == '\'' && !ctx->quotes->in_double)
	{
		ctx->quotes->in_single = !ctx->quotes->in_single;
		if (!ft_process_char(value, i, ctx->expanded))
		{
			free(*ctx->expanded);
			return (0);
		}
		return (1);
	}
	return (-1);
}

int	process_expansion_char_with_quotes(const char *value, int *i,
		t_expand_ctx *ctx)
{
	int	result;

	result = ft_process_single_quote_exp(value, i, ctx);
	if (result != -1)
		return (result);
	result = ft_process_double_quote_exp(value, i, ctx);
	if (result != -1)
		return (result);
	result = ft_process_variable_exp(value, i, ctx);
	if (result != -1)
		return (result);
	if (!ft_process_char(value, i, ctx->expanded))
	{
		free(*ctx->expanded);
		return (0);
	}
	return (1);
}

char	*ft_expand_variable(const char *value, t_data *data)
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
		if (!process_expansion_char_with_quotes(value, &i, &ctx))
			return (NULL);
	}
	return (expanded);
}
