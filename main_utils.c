/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 22:24:25 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef ECHOCTL
# define ECHOCTL 0000400
#endif

void	disable_echo(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}

void	enable_echo(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}

char	*display_prompt(void)
{
	return (ft_strdup("minishell$ "));
}

void	cleanup_and_exit(t_data *data, int status)
{
	enable_echo();
	ft_free_data(data);
	rl_clear_history();
	exit(status);
}

void	init_shell(t_data *data, char **envp)
{
	ft_init_data(data);
	init_env(data, envp);
	disable_echo();
	setup_signals();
}
