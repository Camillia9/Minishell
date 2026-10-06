/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:16:14 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*get_command_at_index(t_command *commands, int index)
{
	t_command	*cmd;
	int			i;

	cmd = commands;
	i = 0;
	while (cmd && i < index)
	{
		cmd = cmd->next;
		i++;
	}
	return (cmd);
}

void	ft_close_child_pipes(int **pipes, int pipe_count)
{
	int	j;

	j = 0;
	while (j < pipe_count)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void	ft_close_parent_fds(t_command *cmd)
{
	if (cmd->input_fd != -1 && cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	if (cmd->output_fd != -1 && cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
}

void	ft_close_pipes(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}
