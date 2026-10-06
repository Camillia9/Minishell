/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:16:14 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

int	restore_fds(int stdin_backup, int stdout_backup, int return_value)
{
	if (stdin_backup != -1)
	{
		dup2(stdin_backup, STDIN_FILENO);
		close(stdin_backup);
	}
	if (stdout_backup != -1)
	{
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdout_backup);
	}
	return (return_value);
}

int	execute_command(t_command *cmd, t_data *data)
{
	int				stdin_backup;
	int				stdout_backup;
	int				status;
	t_exec_params	params;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	params.data = data;
	params.cmd = cmd;
	params.input_fd = stdin_backup;
	params.output_fd = stdout_backup;
	params.index = 0;
	status = ft_execute_single_command(&params);
	if (cmd->input_fd != -1 && cmd->input_fd != STDIN_FILENO)
	{
		close(cmd->input_fd);
		cmd->input_fd = -1;
	}
	if (cmd->output_fd != -1 && cmd->output_fd != STDOUT_FILENO)
	{
		close(cmd->output_fd);
		cmd->output_fd = -1;
	}
	return (restore_fds(stdin_backup, stdout_backup, status));
}

int	init_output_files(t_data *data)
{
	t_token	*token;
	int		in_first_cmd;

	token = data->tokens;
	in_first_cmd = 1;
	while (token)
	{
		if (token->type == PIPE)
		{
			in_first_cmd = 0;
		}
		else if ((token->type == REDIR_OUT || token->type == REDIR_APPEND)
			&& token->next && token->next->type == WORD)
		{
			if (!in_first_cmd && !handle_output_redir(token, data))
				return (0);
		}
		token = token->next;
	}
	return (1);
}

int	check_file_permissions(char *filename, int is_output)
{
	DIR	*dir;

	dir = opendir(filename);
	if (dir)
	{
		closedir(dir);
		return (0);
	}
	if (is_output)
	{
		if (access(filename, F_OK) == 0 && access(filename, W_OK) == -1)
			return (0);
	}
	else
	{
		if (access(filename, F_OK) == -1 || access(filename, R_OK) == -1)
			return (0);
	}
	return (1);
}

int	handle_input_redir(t_token *token, t_data *data)
{
	if (!check_file_permissions(token->next->value, 0))
	{
		data->exit_status = 1;
		return (0);
	}
	return (1);
}
