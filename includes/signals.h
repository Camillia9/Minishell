/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/25 04:00:39 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "types.h"
# include <signal.h>

extern volatile sig_atomic_t	g_signal;

// General signal management
void							setup_signals(void);
void							exec_command_signal(char *cmd, char **args,
									char **env, t_data *data);

// Heredoc signal handling
void							setup_heredoc_signals(void);
char							*heredoc_mode(char *heredoc_delim,
									t_data *data);
char							*verif_signal(char *heredoc_content,
									t_data *data);
char							*process_heredoc(char *heredoc_delim,
									t_data *data);

// Signal utilities
char							*process_heredoc_line(char *line, t_data *data);
char							*append_to_heredoc(char *heredoc_content,
									char *line_with_newline);
void							set_exit_status(t_data *data, int status);
int								get_exit_status(t_data *data);

// Heredoc utilities
void							cleanup_child_data(t_data *data);
int								process_heredoc_line_input(char *delimiter,
									t_data *data, int pipefd);
char							*expand_content(char *content, char *buffer,
									int total_len, int bytes_read);
char							*read_from_pipe(int pipefd);

#endif
