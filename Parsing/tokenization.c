/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:16:14 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_new_token(char *val, t_token_type type, int sq, int dq)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		exit(1);
	if (val)
		token->value = ft_strdup(val);
	else
		token->value = NULL;
	token->type = type;
	token->quoted_single = sq;
	token->quoted_double = dq;
	token->next = NULL;
	return (token);
}

void	ft_add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	ft_handle_operator(t_token **tokens, const char *line, int *i)
{
	if (line[*i] == '|')
		return (ft_add_token(tokens, ft_new_token("|", PIPE, 0, 0)), (*i)++, 0);
	else if (line[*i] == '>' && line[*i + 1] == '>')
		return (ft_add_token(tokens, ft_new_token(">>", REDIR_APPEND, 0, 0)), *i
			+= 2, 0);
	else if (line[*i] == '>')
		return (ft_add_token(tokens, ft_new_token(">", REDIR_OUT, 0, 0)),
			(*i)++, 0);
	else if (line[*i] == '<' && line[*i + 1] == '<')
		return (ft_add_token(tokens, ft_new_token("<<", HEREDOC, 0, 0)), *i
			+= 2, 0);
	else if (line[*i] == '<')
		return (ft_add_token(tokens, ft_new_token("<", REDIR_IN, 0, 0)), (*i)++,
			0);
	return (0);
}

void	ft_parse_word(t_token **tokens, const char *line, int *i,
		t_quotes *quotes)
{
	int	start;
	int	sq_state;
	int	dq_state;

	sq_state = quotes->in_single;
	dq_state = quotes->in_double;
	if (line[*i] == '$' && (line[*i + 1] == '\'' || line[*i + 1] == '"'))
		(*i)++;
	start = *i;
	while (line[*i])
	{
		if (quotes->in_single || quotes->in_double)
		{
			ft_update_quotes_state(line, i, quotes);
			continue ;
		}
		if (is_space(line[*i]) || ft_is_operator_char(line[*i]))
			break ;
		ft_update_quotes_state(line, i, quotes);
	}
	quotes->in_single = sq_state;
	quotes->in_double = dq_state;
	ft_add_word_token(tokens, &line[start], *i - start, quotes);
}

void	ft_copy_char(const char *str, int *i, char *result, int *j)
{
	result[*j] = str[*i];
	(*j)++;
	(*i)++;
}
