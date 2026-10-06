/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/25 03:10:14 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	signal_handler(int signum)
{
	g_signal = signum;
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	child_process(char *cmd, char **args, char **env)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		perror("minishell: signal (SIGINT)");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		perror("minishell: signal (SIGQUIT)");
	execve(cmd, args, env);
	perror("minishell : execve");
	exit(EXIT_FAILURE);
}

static void	handle_child_status(int status, t_data *data)
{
	int	term_signal;

	if (WIFSIGNALED(status))
	{
		term_signal = WTERMSIG(status);
		set_exit_status(data, term_signal + 128);
		if (term_signal == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	}
	else if (WIFEXITED(status))
		set_exit_status(data, WEXITSTATUS(status));
}

void	exec_command_signal(char *cmd, char **args, char **env, t_data *data)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		set_exit_status(data, 1);
		setup_signals();
		return ;
	}
	else if (pid == 0)
		child_process(cmd, args, env);
	else
	{
		waitpid(pid, &status, 0);
		setup_signals();
		handle_child_status(status, data);
	}
}
