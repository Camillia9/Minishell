/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:50:23 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_data(t_data *data)
{
	data->commands = NULL;
	data->env = NULL;
	data->tokens = NULL;
	data->cmd_count = 0;
	data->exit_status = 0;
}

void	ft_init_quotes(t_quotes *quotes)
{
	quotes->in_single = 0;
	quotes->in_double = 0;
	quotes->has_single = 0;
	quotes->has_double = 0;
}

t_command	*ft_new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->name_cmd = NULL;
	cmd->last_infile_heredoc = false;
	cmd->args = NULL;
	cmd->arg_count = 0;
	cmd->input_fd = 0;
	cmd->output_fd = 0;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append_file = NULL;
	cmd->heredoc_delim = NULL;
	cmd->heredoc_content = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_token	*ft_lexer(const char *line)
{
	t_token		*tokens;
	int			i;
	t_quotes	quotes;

	tokens = NULL;
	i = 0;
	ft_init_quotes(&quotes);
	ft_process_line(&tokens, line, &i, &quotes);
	return (tokens);
}

void	ft_process_line(t_token **tokens, const char *line, int *i,
		t_quotes *quotes)
{
	while (line[*i])
	{
		if (is_space(line[*i]) && !quotes->in_single && !quotes->in_double)
			(*i)++;
		else if (!quotes->in_double && !quotes->in_single
			&& ft_is_operator_char(line[*i]))
			ft_handle_operator(tokens, line, i);
		else if (line[*i])
			ft_parse_word(tokens, line, i, quotes);
	}
}
