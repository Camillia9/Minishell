/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 04:00:00 by camansou          #+#    #+#             */
/*   Updated: 2025/05/25 05:28:13 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_command_in_list(t_command *cmd, t_data *data)
{
	t_command	*temp;

	temp = data->commands;
	while (temp)
	{
		if (temp == cmd)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	add_command_to_list(t_command *cmd, t_data *data)
{
	cmd->next = data->commands;
	data->commands = cmd;
	data->cmd_count++;
}

void	remove_command_from_list(t_command *cmd, t_data *data)
{
	data->commands = cmd->next;
	cmd->next = NULL;
	data->cmd_count--;
}

int	manage_command_in_list(t_command *cmd, t_data *data, int add)
{
	int	was_in_list;

	was_in_list = check_command_in_list(cmd, data);
	if (add && !was_in_list)
		add_command_to_list(cmd, data);
	else if (!add && was_in_list)
		remove_command_from_list(cmd, data);
	return (was_in_list);
}
