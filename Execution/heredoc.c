/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/25 02:59:58 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_expanded_line(int fd, char *line, t_data *data)
{
	char	*expanded_line;

	expanded_line = ft_expand_variable(line, data);
	if (expanded_line)
	{
		write(fd, expanded_line, ft_strlen(expanded_line));
		free(expanded_line);
	}
	else
	{
		write(fd, line, ft_strlen(line));
	}
}

void	process_heredoc_input(int fd, char *limiter, int dup_stdin,
		t_data *data)
{
	char	*line;

	g_signal = 0;
	while (1)
	{
		ft_putstr_fd("> ", 2);
		line = get_next_line(dup_stdin);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& (line[ft_strlen(limiter)] == '\n'
				|| line[ft_strlen(limiter)] == '\0'))
		{
			free(line);
			break ;
		}
		write_expanded_line(fd, line, data);
		free(line);
		if (g_signal == 1)
			break ;
	}
}

int	heredoc_child_process(int fd[2], char *limiter, t_data *data)
{
	int	dup_stdin;

	close(fd[0]);
	dup_stdin = dup(0);
	process_heredoc_input(fd[1], limiter, dup_stdin, data);
	close(fd[1]);
	get_next_line(-1);
	close(dup_stdin);
	ft_free_data(data);
	exit(g_signal);
}

int	wait_for_heredoc(pid_t pid, int fd[2])
{
	int	status;

	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}

int	magie_heredoc(t_data *data, char *limiter, int in, int out)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		close(in);
		close(out);
		heredoc_child_process(fd, limiter, data);
	}
	return (wait_for_heredoc(pid, fd));
}
