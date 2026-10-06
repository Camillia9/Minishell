/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/25 02:59:58 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>

void	execute_not_builtin_child_process(t_data *data, t_command *cmd)
{
	char		**envp;
	char		*cmd_path;
	struct stat	sb;

	handle_cmd_redirections(cmd);
	envp = env_to_str_array(data->env);
	cmd_path = get_cmd_path(cmd->name_cmd, data->env);
	g_signal = 0;
	if (!cmd_path)
		handle_no_cmd_path_error(cmd, envp, data);
	if (stat(cmd_path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd(cmd->name_cmd, 2);
		ft_putendl_fd(": is a directory", 2);
		free_tab(envp);
		ft_free_data(data);
		exit(126);
	}
	execve(cmd_path, cmd->args, envp);
	handle_execve_error(cmd, envp, data);
}

void	setup_child_pipes(t_pipeline_child_params *pc_params)
{
	if (pc_params->prev_pipe_read != -1)
	{
		if (!has_redir(pc_params->data, pc_params->cmd_index, 0))
		{
			if (dup2(pc_params->prev_pipe_read, STDIN_FILENO) == -1)
				exit(1);
		}
		close(pc_params->prev_pipe_read);
	}
	if (pc_params->cmd_index < pc_params->data->cmd_count - 1)
	{
		close(pc_params->pipe_fd[0]);
		if (!has_redir(pc_params->data, pc_params->cmd_index, 1))
		{
			if (dup2(pc_params->pipe_fd[1], STDOUT_FILENO) == -1)
				exit(1);
		}
		close(pc_params->pipe_fd[1]);
	}
}

void	exec_child_process(t_pipeline_child_params *pc_params)
{
	t_exec_params	params;
	int				status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_child_pipes(pc_params);
	params.data = pc_params->data;
	params.cmd = pc_params->cmd;
	params.input_fd = 0;
	params.output_fd = 0;
	params.index = pc_params->cmd_index;
	status = ft_execute_single_command(&params);
	ft_free_data(pc_params->data);
	exit(status);
}

int	handle_child_process(t_exec_params *params)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (params->input_fd > 0)
		close(params->input_fd);
	if (params->output_fd > 0)
		close(params->output_fd);
	execute_not_builtin_child_process(params->data, params->cmd);
	exit(127);
}

int	handle_external_command(t_exec_params *params)
{
	struct sigaction	sa_ignore;
	struct sigaction	sa_oldint;
	struct sigaction	sa_oldquit;
	pid_t				pid;

	setup_signal_handling(&sa_ignore, &sa_oldint, &sa_oldquit);
	pid = fork();
	if (pid == -1)
	{
		sigaction(SIGINT, &sa_oldint, NULL);
		sigaction(SIGQUIT, &sa_oldquit, NULL);
		return (1);
	}
	if (pid == 0)
		handle_child_process(params);
	return (cleanup_parent_process(params, pid, sa_oldint, sa_oldquit));
}
