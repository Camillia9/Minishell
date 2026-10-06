/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 21:52:43 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_heredoc_line(char *line, t_data *data)
{
	char	*expanded_line;
	char	*source_line;
	char	*line_with_newline;

	expanded_line = ft_expand_variable(line, data);
	if (expanded_line)
		source_line = expanded_line;
	else
		source_line = line;
	line_with_newline = malloc(ft_strlen(source_line) + 2);
	if (line_with_newline)
	{
		ft_strcpy(line_with_newline, source_line);
		ft_strcat(line_with_newline, "\n");
	}
	if (expanded_line)
		free(expanded_line);
	return (line_with_newline);
}

char	*append_to_heredoc(char *heredoc_content, char *line_with_newline)
{
	char	*tmp;

	if (!heredoc_content)
	{
		if (line_with_newline)
			return (ft_strdup(line_with_newline));
		else
			return (ft_strdup(""));
	}
	else
	{
		if (line_with_newline)
		{
			tmp = ft_strjoin(heredoc_content, line_with_newline);
			free(heredoc_content);
			return (tmp);
		}
	}
	return (heredoc_content);
}

void	set_exit_status(t_data *data, int status)
{
	data->exit_status = status;
}

int	get_exit_status(t_data *data)
{
	return (data->exit_status);
}
