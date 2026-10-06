/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 03:55:00 by camansou          #+#    #+#             */
/*   Updated: 2025/05/25 04:00:39 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_child_data(t_data *data)
{
	if (data->tokens)
		ft_free_tokens(data->tokens);
	if (data->env)
		ft_free_env(data->env);
	if (data->commands)
		ft_free_commands(data);
	rl_clear_history();
}

int	process_heredoc_line_input(char *delimiter, t_data *data, int pipefd)
{
	char	*line;
	char	*processed;

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
		{
			if (line)
				free(line);
			break ;
		}
		processed = process_heredoc_line(line, data);
		write(pipefd, processed, ft_strlen(processed));
		free(processed);
		free(line);
	}
	return (0);
}

char	*expand_content(char *content, char *buffer, int total_len,
		int bytes_read)
{
	char	*temp;

	temp = malloc(total_len + bytes_read + 1);
	if (!temp)
		return (NULL);
	if (total_len > 0)
		ft_strcpy(temp, content);
	else
		temp[0] = '\0';
	ft_strcat(temp, buffer);
	free(content);
	return (temp);
}

char	*read_from_pipe(int pipefd)
{
	char	*content;
	char	buffer[1024];
	int		bytes_read;
	int		total_len;

	content = malloc(1);
	if (!content)
		return (NULL);
	content[0] = '\0';
	total_len = 0;
	bytes_read = read(pipefd, buffer, 1023);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		content = expand_content(content, buffer, total_len, bytes_read);
		if (!content)
			break ;
		total_len += bytes_read;
		bytes_read = read(pipefd, buffer, 1023);
	}
	return (content);
}
