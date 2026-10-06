/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:16:14 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell.h"
#include "minishell.h"
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>

bool	check_token_redir(t_token *tmp, int opt)
{
	if (opt == 1)
	{
		if (tmp->type == REDIR_APPEND || tmp->type == REDIR_OUT)
			return (1);
	}
	else if (opt == 0)
	{
		if (tmp->type == REDIR_IN || tmp->type == HEREDOC)
			return (1);
	}
	return (0);
}

bool	has_redir(t_data *data, int nb_cmd, int opt)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = data->tokens;
	while (i < nb_cmd)
	{
		if (tmp->type == PIPE)
			i++;
		tmp = tmp->next;
	}
	while (tmp && tmp->type != PIPE)
	{
		if (check_token_redir(tmp, opt))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	handle_cmd_redirections(t_command *cmd)
{
	if (cmd->input_fd > 0 && cmd->input_fd != STDIN_FILENO)
	{
		if (dup2(cmd->input_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input");
			return (0);
		}
		close(cmd->input_fd);
	}
	if (cmd->output_fd > 0 && cmd->output_fd != STDOUT_FILENO)
	{
		if (dup2(cmd->output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output");
			return (0);
		}
		close(cmd->output_fd);
	}
	return (1);
}

int	wait_for_child(pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

t_token	*find_command_tokens(t_exec_params *params)
{
	t_token	*tmp;
	int		i;

	tmp = params->data->tokens;
	i = 0;
	while (tmp && i < params->index)
	{
		if (tmp->type == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (tmp);
}
