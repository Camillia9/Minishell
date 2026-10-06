/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 03:57:00 by camansou          #+#    #+#             */
/*   Updated: 2025/05/25 04:00:39 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	allocate_heredoc_strings(t_command *cmd, char *delim)
{
	char	*delim_copy;

	delim_copy = ft_strdup(delim);
	if (!delim_copy)
		return (0);
	cmd->heredoc_delim = delim_copy;
	cmd->heredoc_content = ft_strdup("");
	if (!cmd->heredoc_content)
	{
		free(cmd->heredoc_delim);
		cmd->heredoc_delim = NULL;
		return (0);
	}
	return (1);
}

int	setup_heredoc_content(t_command *cmd, char *content, char *delim)
{
	char	*delim_copy;

	if (content)
	{
		delim_copy = ft_strdup(delim);
		if (!delim_copy)
		{
			free(content);
			return (0);
		}
		cmd->heredoc_delim = delim_copy;
		cmd->heredoc_content = content;
		return (1);
	}
	return (allocate_heredoc_strings(cmd, delim));
}

void	cleanup_existing_heredoc(t_command *cmd)
{
	if (cmd->heredoc_content)
	{
		free(cmd->heredoc_content);
		cmd->heredoc_content = NULL;
	}
	if (cmd->heredoc_delim)
	{
		free(cmd->heredoc_delim);
		cmd->heredoc_delim = NULL;
	}
}
