/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
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

void	handle_execve_error(t_command *cmd, char **envp, t_data *data)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd(cmd->name_cmd, 2);
		ft_putendl_fd(": command not found", 2);
	}
	else if (errno == EISDIR)
	{
		ft_putstr_fd(cmd->name_cmd, 2);
		ft_putendl_fd(": is a directory", 2);
	}
	else
	{
		ft_putstr_fd(cmd->name_cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	free_tab(envp);
	ft_free_data(data);
	if (errno == ENOENT)
		exit(127);
	else
		exit(126);
}

void	handle_file_not_found(t_command *cmd, char **envp, t_data *data)
{
	ft_putstr_fd(cmd->name_cmd, 2);
	ft_putendl_fd(": No such file or directory", 2);
	free_tab(envp);
	ft_free_data(data);
	exit(127);
}

void	handle_permission_denied(t_command *cmd, char **envp, t_data *data)
{
	ft_putstr_fd(cmd->name_cmd, 2);
	ft_putendl_fd(": Permission denied", 2);
	free_tab(envp);
	ft_free_data(data);
	exit(126);
}

void	handle_no_cmd_path_error(t_command *cmd, char **envp, t_data *data)
{
	if (cmd->name_cmd[0] == '/' || ft_strncmp(cmd->name_cmd, "./", 2) == 0
		|| ft_strncmp(cmd->name_cmd, "../", 3) == 0)
	{
		if (access(cmd->name_cmd, F_OK) != 0)
			handle_file_not_found(cmd, envp, data);
		else
			handle_permission_denied(cmd, envp, data);
	}
	ft_putstr_fd(cmd->name_cmd, 2);
	ft_putendl_fd(": command not found", 2);
	free_tab(envp);
	rl_clear_history();
	ft_free_data(data);
	exit(127);
}

int	handle_pipe_error(int prev_pipe_read, struct sigaction sa_oldint,
		struct sigaction sa_oldquit)
{
	if (prev_pipe_read != -1)
		close(prev_pipe_read);
	sigaction(SIGINT, &sa_oldint, NULL);
	sigaction(SIGQUIT, &sa_oldquit, NULL);
	return (1);
}
