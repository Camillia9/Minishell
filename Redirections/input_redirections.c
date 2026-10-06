/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/25 03:29:53 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_redirection(t_command *cmd)
{
	int	fd;

	if (access(cmd->input_file, F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->input_file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (0);
	}
	if (access(cmd->input_file, R_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->input_file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (0);
	}
	fd = open(cmd->input_file, O_RDONLY);
	if (fd == -1)
		return (0);
	cmd->input_fd = fd;
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), 0);
	close(fd);
	return (1);
}

int	heredoc_redirection(t_command *cmd, t_data *data, int pipe_index)
{
	int		pipe_fds[2];
	t_token	*tmp;
	char	*heredoc_content;
	bool	malloc_heredoc;

	malloc_heredoc = false;
	if (pipe(pipe_fds) == -1)
		return (-1);
	tmp = find_pipe_posi(data->tokens, pipe_index);
	heredoc_content = process_heredoc_tokens(tmp, data, &malloc_heredoc);
	if (!heredoc_content && malloc_heredoc)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		return (-1);
	}
	if (setup_heredoc_pipe(pipe_fds, heredoc_content, malloc_heredoc) == -1)
		return (-1);
	return (finalize_heredoc(cmd, pipe_fds));
}

t_token	*find_pipe_posi(t_token *tokens, int pipe_index)
{
	t_token	*tmp;
	int		i;

	tmp = tokens;
	i = 0;
	while (tmp && i < pipe_index)
	{
		if (tmp->type == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (tmp);
}

char	*process_heredoc_tokens(t_token *tmp, t_data *data,
		bool *malloc_heredoc)
{
	char	*heredoc_content;

	heredoc_content = NULL;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == HEREDOC)
		{
			*malloc_heredoc = true;
			tmp = tmp->next;
			if (heredoc_content)
				free(heredoc_content);
			heredoc_content = process_heredoc(tmp->value, data);
			if (!heredoc_content)
				return (NULL);
		}
		tmp = tmp->next;
	}
	return (heredoc_content);
}

int	setup_heredoc_pipe(int pipe_fds[2], char *heredoc_content,
		bool malloc_heredoc)
{
	if (malloc_heredoc && !heredoc_content)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		return (-1);
	}
	if (malloc_heredoc)
	{
		ft_putstr_fd(heredoc_content, pipe_fds[1]);
		free(heredoc_content);
	}
	close(pipe_fds[1]);
	return (1);
}
