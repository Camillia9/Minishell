/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/25 03:44:32 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	ft_free_command_args(cmd);
	ft_free_command_redirs(cmd);
	if (cmd->name_cmd)
		free(cmd->name_cmd);
	free(cmd);
}

void	ft_free_commands(t_data *data)
{
	t_command	*current;
	t_command	*next;

	if (!data || !data->commands)
		return ;
	current = data->commands;
	while (current)
	{
		next = current->next;
		ft_free_command(current);
		current = next;
	}
	data->commands = NULL;
	data->cmd_count = 0;
}

int	ft_add_arg(t_command *cmd, char *arg)
{
	char	**new_args;
	int		i;

	new_args = malloc(sizeof(char *) * (cmd->arg_count + 2));
	if (!new_args)
		return (0);
	i = 0;
	while (i < cmd->arg_count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
	cmd->arg_count++;
	return (1);
}

void	ft_add_command(t_data *data, t_command *cmd)
{
	t_command	*temp;

	if (!cmd)
		return ;
	if (!data->commands)
		data->commands = cmd;
	else
	{
		temp = data->commands;
		while (temp->next)
			temp = temp->next;
		temp->next = cmd;
	}
	data->cmd_count++;
}

int	ft_parse_commands(t_data *data)
{
	t_command		*current_cmd;
	t_token			*current;
	int				expecting_target;
	t_token_type	last_type;
	t_parse_state	state;

	ft_init_parsing(data, &current_cmd, &expecting_target, &last_type);
	state.current_cmd = &current_cmd;
	state.expecting_target = &expecting_target;
	state.last_type = &last_type;
	state.data = data;
	current = data->tokens;
	while (current)
	{
		if (!process_single_token(current, &state))
			return (0);
		current = current->next;
	}
	return (finalize_last_command(current_cmd, data));
}
