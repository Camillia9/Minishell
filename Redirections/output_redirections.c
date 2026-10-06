/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:16:14 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

int	output_redirection(t_command *cmd)
{
	int	fd;

	fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->output_file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (0);
	}
	cmd->output_fd = fd;
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	append_redirection(t_command *cmd)
{
	int	fd;

	fd = open(cmd->append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->append_file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (0);
	}
	cmd->output_fd = fd;
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	handle_output_redir(t_token *token, t_data *data)
{
	int	fd;
	int	flags;

	if (!check_file_permissions(token->next->value, 1))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token->next->value, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		data->exit_status = 1;
		return (0);
	}
	if (token->type == REDIR_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(token->next->value, flags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(token->next->value);
		data->exit_status = 1;
		return (0);
	}
	close(fd);
	return (1);
}

int	finalize_heredoc(t_command *cmd, int pipe_fds[2])
{
	if (cmd->last_infile_heredoc)
	{
		if (cmd->input_fd > 0)
			close(cmd->input_fd);
		cmd->input_fd = pipe_fds[0];
		return (1);
	}
	else
	{
		close(pipe_fds[0]);
		return (1);
	}
}
