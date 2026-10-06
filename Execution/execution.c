/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 19:01:13 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <signal.h> // Required for struct sigaction
#include <sys/stat.h>

int	ft_execute_pipeline(t_data *data)
{
	int					prev_pipe_read;
	struct sigaction	sa_oldint;
	struct sigaction	sa_oldquit;

	setup_pipeline_signals(&sa_oldint, &sa_oldquit);
	prev_pipe_read = -1;
	return (execute_pipeline_loop(data, &prev_pipe_read, sa_oldint,
			sa_oldquit));
}

int	ft_execute_single_command(t_exec_params *params)
{
	int	status;

	if (!params->cmd->name_cmd || params->cmd->name_cmd[0] == '\0')
	{
		ft_putendl_fd(": command not found", 2);
		return (127);
	}
	if (process_redirections(params))
		return (1);
	setup_file_descriptors(params);
	if (is_builtin(params->cmd->name_cmd))
	{
		if (ft_strncmp("exit", params->cmd->name_cmd, 5) == 0)
		{
			if (params->input_fd > 0)
				close(params->input_fd);
			if (params->output_fd > 0)
				close(params->output_fd);
		}
		return (execute_builtin(params->cmd->args, &params->data->env,
				&status));
	}
	return (handle_external_command(params));
}
