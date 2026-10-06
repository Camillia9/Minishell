/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/25 03:44:07 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_commands(t_data *data)
{
	int	status;

	if (!init_output_files(data))
		return (data->exit_status);
	status = 0;
	if (data->cmd_count == 1)
		status = execute_command(data->commands, data);
	else if (data->cmd_count > 1)
		status = ft_execute_pipeline(data);
	return (status);
}

void	process_input(t_data *data, char *line)
{
	int	parse_result;
	int	status;

	add_history(line);
	parse_result = ft_check_and_parse(data, line);
	if (parse_result)
	{
		status = execute_commands(data);
		set_exit_status(data, status);
	}
	else
	{
		set_exit_status(data, 2);
	}
}

void	cleanup_iteration(t_data *data, char *line)
{
	free(line);
	if (data->tokens)
		ft_free_tokens(data->tokens);
	if (data->commands)
		ft_free_commands(data);
	data->tokens = NULL;
	data->commands = NULL;
	data->cmd_count = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;
	char	*prompt;

	(void)argc;
	(void)argv;
	init_shell(&data, envp);
	while (1)
	{
		setup_signals();
		prompt = display_prompt();
		line = readline(prompt);
		free(prompt);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (line[0] != '\0')
			process_input(&data, line);
		cleanup_iteration(&data, line);
	}
	cleanup_and_exit(&data, get_exit_status(&data));
	return (get_exit_status(&data));
}
