/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:36:45 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "types.h"

// Input redirections
int		input_redirection(t_command *cmd);
int		heredoc_redirection(t_command *cmd, t_data *data, int pipe_index);
t_token	*find_pipe_posi(t_token *tokens, int pipe_index);
char	*process_heredoc_tokens(t_token *tmp, t_data *data,
			bool *malloc_heredoc);
int		setup_heredoc_pipe(int pipe_fds[2], char *heredoc_content,
			bool malloc_heredoc);

// Output redirections
int		output_redirection(t_command *cmd);
int		append_redirection(t_command *cmd);
int		handle_output_redir(t_token *token, t_data *data);
int		finalize_heredoc(t_command *cmd, int pipe_fds[2]);

// Redirection execution
int		restore_fds(int stdin_backup, int stdout_backup, int return_value);
int		execute_command(t_command *cmd, t_data *data);
int		init_output_files(t_data *data);
int		check_file_permissions(char *filename, int is_output);
int		handle_input_redir(t_token *token, t_data *data);

// Legacy function
int		magie_heredoc(t_data *data, char *limiter, int in, int out);

#endif
