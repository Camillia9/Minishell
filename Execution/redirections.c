/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:25:00 by camansou          #+#    #+#             */
/*   Updated: 2025/05/25 02:59:58 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>

int	process_redir_in(t_exec_params *params, t_token **tmp)
{
	params->cmd->last_infile_heredoc = false;
	if (params->cmd->input_fd > 0)
		close(params->cmd->input_fd);
	*tmp = (*tmp)->next;
	params->cmd->input_fd = open((*tmp)->value, O_RDONLY, 0644);
	if (params->cmd->input_fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror((*tmp)->value);
		set_exit_status(params->data, 1);
		return (1);
	}
	return (0);
}

int	process_redir_out(t_exec_params *params, t_token **tmp)
{
	if (params->cmd->output_fd > 0)
		close(params->cmd->output_fd);
	*tmp = (*tmp)->next;
	params->cmd->output_fd = open((*tmp)->value, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (params->cmd->output_fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror((*tmp)->value);
		set_exit_status(params->data, 1);
		return (1);
	}
	return (0);
}

int	process_redir_append(t_exec_params *params, t_token **tmp)
{
	if (params->cmd->output_fd > 0)
		close(params->cmd->output_fd);
	*tmp = (*tmp)->next;
	params->cmd->output_fd = open((*tmp)->value, O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (params->cmd->output_fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror((*tmp)->value);
		set_exit_status(params->data, 1);
		return (1);
	}
	return (0);
}

int	process_redirections(t_exec_params *params)
{
	t_token	*tmp;

	tmp = find_command_tokens(params);
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIR_IN && process_redir_in(params, &tmp))
			return (1);
		else if (tmp->type == REDIR_OUT && process_redir_out(params, &tmp))
			return (1);
		else if (tmp->type == REDIR_APPEND && process_redir_append(params,
				&tmp))
			return (1);
		else if (tmp->type == HEREDOC)
			process_heredoc_redirection(params, &tmp);
		tmp = tmp->next;
	}
	return (0);
}

int	setup_file_descriptors(t_exec_params *params)
{
	if (params->cmd->output_fd > 0)
	{
		if (dup2(params->cmd->output_fd, STDOUT_FILENO) == -1)
		{
			close(params->cmd->output_fd);
			ft_free_data(params->data);
			exit(128);
		}
	}
	if (params->cmd->input_fd > 0)
	{
		if (dup2(params->cmd->input_fd, STDIN_FILENO) == -1)
		{
			close(params->cmd->input_fd);
			ft_free_data(params->data);
			exit(128);
		}
	}
	return (0);
}
