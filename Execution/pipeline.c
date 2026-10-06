/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:28:35 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell.h"
#include "minishell.h"
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>

void	setup_pipeline_signals(struct sigaction *sa_oldint,
		struct sigaction *sa_oldquit)
{
	struct sigaction	sa_ignore;

	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sigaction(SIGINT, &sa_ignore, sa_oldint);
	sigaction(SIGQUIT, &sa_ignore, sa_oldquit);
}

int	wait_all_children(t_data *data, pid_t last_pid, struct sigaction sa_oldint,
		struct sigaction sa_oldquit)
{
	pid_t	wpid;
	int		wstatus;
	int		last_status;
	int		i;

	last_status = 0;
	i = 0;
	while (i < data->cmd_count)
	{
		wpid = waitpid(0, &wstatus, WUNTRACED);
		if (wpid == last_pid)
			last_status = wstatus;
		i++;
	}
	sigaction(SIGINT, &sa_oldint, NULL);
	sigaction(SIGQUIT, &sa_oldquit, NULL);
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	return (last_status);
}

pid_t	execute_pipeline_child(t_pipeline_child_params *pc_params)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exec_child_process(pc_params);
	return (pid);
}

int	setup_pipeline_params(t_data *data, int *prev_pipe_read, int i,
		t_command *tmp)
{
	t_pipeline_child_params	pc_params;
	int						pipe_fd[2];
	pid_t					pid;

	if (i < data->cmd_count - 1 && pipe(pipe_fd) == -1)
		return (-2);
	pc_params.data = data;
	pc_params.pipe_fd[0] = pipe_fd[0];
	pc_params.pipe_fd[1] = pipe_fd[1];
	pc_params.prev_pipe_read = *prev_pipe_read;
	pc_params.cmd_index = i;
	pc_params.cmd = tmp;
	pid = execute_pipeline_child(&pc_params);
	if (pid == -1)
		return (-1);
	if (*prev_pipe_read != -1)
		close(*prev_pipe_read);
	if (i < data->cmd_count - 1)
	{
		close(pipe_fd[1]);
		*prev_pipe_read = pipe_fd[0];
	}
	return (pid);
}

int	execute_pipeline_loop(t_data *data, int *prev_pipe_read,
		struct sigaction sa_oldint, struct sigaction sa_oldquit)
{
	int			i;
	t_command	*tmp;
	pid_t		last_pid;
	pid_t		pid;

	i = 0;
	tmp = data->commands;
	last_pid = -1;
	while (i < data->cmd_count)
	{
		pid = setup_pipeline_params(data, prev_pipe_read, i, tmp);
		if (pid == -2)
			return (handle_pipe_error(*prev_pipe_read, sa_oldint, sa_oldquit));
		if (pid == -1)
		{
			sigaction(SIGINT, &sa_oldint, NULL);
			sigaction(SIGQUIT, &sa_oldquit, NULL);
			return (1);
		}
		if (i == data->cmd_count - 1)
			last_pid = pid;
		i++;
		tmp = tmp->next;
	}
	return (wait_all_children(data, last_pid, sa_oldint, sa_oldquit));
}
