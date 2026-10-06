/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/25 03:44:32 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

void	ft_free_env(t_env *env_list)
{
	t_env	*current;
	t_env	*next;

	current = env_list;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
}

void	ft_free_data(t_data *data)
{
	if (data->tokens)
		ft_free_tokens(data->tokens);
	if (data->env)
		ft_free_env(data->env);
	if (data->commands)
		ft_free_commands(data);
	rl_clear_history();
}

void	ft_free_command_args(t_command *cmd)
{
	int	i;

	i = 0;
	if (!cmd->args)
		return ;
	while (i < cmd->arg_count)
	{
		if (cmd->args[i])
			free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
}

void	ft_free_command_redirs(t_command *cmd)
{
	if (cmd->input_file)
		free(cmd->input_file);
	if (cmd->output_file)
		free(cmd->output_file);
	if (cmd->append_file)
		free(cmd->append_file);
	if (cmd->heredoc_delim)
		free(cmd->heredoc_delim);
	if (cmd->heredoc_content)
		free(cmd->heredoc_content);
}
