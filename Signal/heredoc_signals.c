/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/25 04:00:39 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_sigint_handler(int signum)
{
	(void)signum;
	exit(130);
}

static char	*read_heredoc_child(char *delimiter, t_data *data, int pipefd)
{
	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	process_heredoc_line_input(delimiter, data, pipefd);
	close(pipefd);
	cleanup_child_data(data);
	exit(0);
}

char	*process_heredoc(char *delimiter, t_data *data)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;
	char	*content;

	if (pipe(pipefd) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
		read_heredoc_child(delimiter, data, pipefd[1]);
	close(pipefd[1]);
	content = read_from_pipe(pipefd[0]);
	close(pipefd[0]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		free(content);
		set_exit_status(data, 130);
		return (NULL);
	}
	if (content)
		return (content);
	return (ft_strdup(""));
}
