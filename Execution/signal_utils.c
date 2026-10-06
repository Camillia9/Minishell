/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:35:00 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 20:39:29 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>

int	setup_signal_handling(struct sigaction *sa_ignore,
		struct sigaction *sa_oldint, struct sigaction *sa_oldquit)
{
	sa_ignore->sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore->sa_mask);
	sa_ignore->sa_flags = 0;
	sigaction(SIGINT, sa_ignore, sa_oldint);
	sigaction(SIGQUIT, sa_ignore, sa_oldquit);
	return (0);
}

int	cleanup_parent_process(t_exec_params *params, pid_t pid,
		struct sigaction sa_oldint, struct sigaction sa_oldquit)
{
	int	ret;

	if (params->cmd->input_fd > 0)
	{
		close(params->cmd->input_fd);
		params->cmd->input_fd = 0;
	}
	if (params->cmd->output_fd > 0)
	{
		close(params->cmd->output_fd);
		params->cmd->output_fd = 0;
	}
	ret = wait_for_child(pid);
	sigaction(SIGINT, &sa_oldint, NULL);
	sigaction(SIGQUIT, &sa_oldquit, NULL);
	return (ret);
}

int	setup_heredoc_empty(t_exec_params *params, int pipe_fds[2])
{
	if (pipe(pipe_fds) == 0)
	{
		close(pipe_fds[1]);
		params->cmd->input_fd = pipe_fds[0];
		params->cmd->last_infile_heredoc = true;
	}
	else
		params->cmd->input_fd = -1;
	return (0);
}

int	process_heredoc_redirection(t_exec_params *params, t_token **tmp)
{
	int	pipe_fds[2];

	if (params->cmd->input_fd > 0)
		close(params->cmd->input_fd);
	*tmp = (*tmp)->next;
	if (params->cmd->heredoc_content
		&& ft_strlen(params->cmd->heredoc_content) > 0)
		return (setup_heredoc_with_content(params, pipe_fds));
	else
		return (setup_heredoc_empty(params, pipe_fds));
}

int	setup_heredoc_with_content(t_exec_params *params, int pipe_fds[2])
{
	ssize_t	written;

	if (pipe(pipe_fds) == 0)
	{
		written = write(pipe_fds[1], params->cmd->heredoc_content,
				ft_strlen(params->cmd->heredoc_content));
		(void)written;
		close(pipe_fds[1]);
		params->cmd->input_fd = pipe_fds[0];
		params->cmd->last_infile_heredoc = true;
	}
	else
		params->cmd->input_fd = -1;
	return (0);
}
