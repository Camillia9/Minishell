/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 16:56:06 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_command_args(t_command *cmd)
{
	int	i;

	printf("  Arguments (%d): ", cmd->arg_count);
	i = 0;
	while (i < cmd->arg_count)
	{
		printf("[%s] ", cmd->args[i]);
		i++;
	}
	printf("\n");
}

void	print_command_redirections(t_command *cmd)
{
	if (cmd->input_file)
		printf("  Redirection entrée: %s\n", cmd->input_file);
	if (cmd->output_file)
		printf("  Redirection sortie: %s\n", cmd->output_file);
	if (cmd->append_file)
		printf("  Redirection append: %s\n", cmd->append_file);
	if (cmd->heredoc_delim)
		printf("  Heredoc: %s\n", cmd->heredoc_delim);
}

void	ft_print_commands(t_data *data)
{
	t_command	*cmd;
	int			cmd_index;

	if (!data || !data->commands)
	{
		printf("Aucune commande\n");
		return ;
	}
	printf("Contient %d commande(s)\n", data->cmd_count);
	cmd = data->commands;
	cmd_index = 0;
	while (cmd)
	{
		printf("Commande %d: %s\n", ++cmd_index, cmd->name_cmd);
		print_command_args(cmd);
		print_command_redirections(cmd);
		printf("\n");
		cmd = cmd->next;
	}
}
