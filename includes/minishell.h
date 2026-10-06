/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/25 03:54:29 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# include "../Libft/get_next_line/get_next_line.h"
# include "../Libft/libft.h"
# include "environment.h"
# include "redirections.h"
# include "signals.h"
# include "types.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

// Utility functions
bool		is_space(char c);
int			ft_is_operator_char(char c);
int			ft_is_var_char(char c);
int			ft_is_redirection(t_token_type type);

// Data initialization
void		ft_init_data(t_data *data);
void		ft_init_quotes(t_quotes *quotes);

// Main utility functions
void		disable_echo(void);
void		enable_echo(void);
char		*display_prompt(void);
void		cleanup_and_exit(t_data *data, int status);
void		init_shell(t_data *data, char **envp);

// Parsing functions
void		ft_parse_line(t_data *data, const char *line);
t_token		*ft_lexer(const char *line);
void		ft_process_line(t_token **tokens, const char *line, int *i,
				t_quotes *quotes);

// Token functions
t_token		*ft_new_token(char *val, t_token_type type, int sq, int dq);
void		ft_add_token(t_token **head, t_token *new);
int			ft_handle_operator(t_token **tokens, const char *line, int *i);
void		ft_parse_word(t_token **tokens, const char *line, int *i,
				t_quotes *quotes);

// Quote handling
void		ft_update_quotes_state(const char *line, int *i, t_quotes *quotes);
void		ft_check_quote_types(char *word, int len, int is_quoted[2]);
int			ft_check_matching_quotes(char *word, int len, char quote_type);
char		*ft_strip_quotes(const char *str, t_quotes *quotes);
char		*ft_process_quotes(const char *str, t_quotes *quotes);
void		ft_handle_quotes(const char *str, int *i, t_quotes *quotes,
				char quote_type);

// Word processing
void		ft_copy_char(const char *str, int *i, char *result, int *j);
t_token		*ft_create_word_token(char *word, t_quotes *quotes);
void		ft_add_word_token(t_token **tokens, const char *start, int len,
				t_quotes *quotes);

// Variable expansion
char		*ft_get_env_value(t_env *env, const char *var);
char		*ft_extract_varname(const char *value, int *i);
char		*ft_join_strings(char *s1, char *s2, int free_s2);
int			ft_process_variable(const char *value, int *i, char **expanded,
				t_data *data);
int			ft_process_char(const char *value, int *i, char **expanded);
char		*ft_expand_variable(const char *value, t_data *data);
char		*ft_expand_and_strip(const char *value, t_data *data);
char		*ft_expand_tilde(const char *str, t_data *data);
void		ft_expand_tokens(t_data *data);
int			process_expansion_char_with_quotes(const char *value, int *i,
				t_expand_ctx *ctx);
void		ft_itoa_simple(int num, char *str);

// Memory management
void		ft_free_tokens(t_token *tokens);
void		ft_free_env(t_env *env_list);
void		ft_free_data(t_data *data);

// Debug functions
char		*ft_get_token_type_str(t_token_type type);
void		ft_print_tokens(t_token *tokens);

// Command functions
t_command	*ft_new_command(void);
int			ft_add_arg(t_command *cmd, char *arg);
void		ft_add_command(t_data *data, t_command *cmd);
int			ft_handle_redirection_target(t_token *token,
				int *expecting_redir_target, t_token_type *last_redir_type);
int			ft_set_redirection_target(t_command *cmd, t_token *token,
				t_token_type last_redir_type, t_data *data);
int			ft_handle_word_token(t_token *token, t_parse_ctx *ctx,
				t_data *data);
void		ft_init_parsing(t_data *data, t_command **current_cmd,
				int *expecting_target, t_token_type *last_type);
int			ft_handle_pipe(t_data *data, t_command **current_cmd);
int			ft_process_token(t_token *token, t_parse_ctx *ctx, t_data *data);
int			ft_parse_commands(t_data *data);

// Command memory management
void		ft_free_command_args(t_command *cmd);
void		ft_free_command_redirs(t_command *cmd);
void		ft_free_command(t_command *cmd);
void		ft_free_commands(t_data *data);
void		ft_print_commands(t_data *data);

// Syntax checking
int			ft_check_syntax_start(t_token *tokens);
void		ft_syntax_token_error(t_token_type type);
int			ft_check_redir_syntax(t_token *token, int *expecting_word);
int			ft_check_pipe_syntax(t_token *token, int *cmd_present);
int			ft_check_syntax(t_token *tokens);
int			ft_check_and_parse(t_data *data, const char *line);
int			ft_check_pipe_redir(t_token *current);

// Path functions
char		*find_path_env(t_env *env_list);
char		*validate_cmd_path(char *base_path, char *cmd);
void		free_tab(char **tab);
char		*get_cmd_path(char *cmd, t_env *env_list);
char		*check_absolute_path(char *cmd);
char		*search_in_paths(char **paths, char *cmd);

// Execution functions
int			ft_execute_pipeline(t_data *data);
int			ft_execute_single_command(t_exec_params *params);
void		execute_not_builtin_child_process(t_data *data, t_command *cmd);
int			handle_cmd_redirections(t_command *cmd);
int			wait_for_child(pid_t pid);

// Pipeline functions
bool		has_redir(t_data *data, int nb_cmd, int opt);
bool		check_token_redir(t_token *tmp, int opt);
void		setup_pipeline_signals(struct sigaction *sa_oldint,
				struct sigaction *sa_oldquit);
int			wait_all_children(t_data *data, pid_t last_pid,
				struct sigaction sa_oldint, struct sigaction sa_oldquit);
pid_t		execute_pipeline_child(t_pipeline_child_params *params);
void		setup_child_pipes(t_pipeline_child_params *pc_params);
void		exec_child_process(t_pipeline_child_params *pc_params);

// Redirection processing
t_token		*find_command_tokens(t_exec_params *params);
int			process_redir_in(t_exec_params *params, t_token **tmp);
int			process_redir_out(t_exec_params *params, t_token **tmp);
int			process_redir_append(t_exec_params *params, t_token **tmp);
int			process_heredoc_redirection(t_exec_params *params, t_token **tmp);
int			setup_file_descriptors(t_exec_params *params);
int			process_redirections(t_exec_params *params);
int			handle_external_command(t_exec_params *params);

// Error handling
int			handle_pipe_error(int prev_pipe_read, struct sigaction sa_oldint,
				struct sigaction sa_oldquit);
int			handle_fork_error(int prev_pipe_read, int pipe_fd[2], int i,
				int cmd_count);
int			execute_pipeline_loop(t_data *data, int *prev_pipe_read,
				struct sigaction sa_oldint, struct sigaction sa_oldquit);
void		handle_no_cmd_path_error(t_command *cmd, char **envp, t_data *data);
void		handle_execve_error(t_command *cmd, char **envp, t_data *data);

// Pipeline utilities
int			ft_setup_pipeline(t_data *data, int cmd_count, int ***pipes);
int			ft_init_pipes(int **pipes, int pipe_count);
t_command	*get_command_at_index(t_command *commands, int index);
void		ft_setup_pipe_io(int **pipes, int i, int cmd_count);
void		ft_close_child_pipes(int **pipes, int pipe_count);
void		ft_handle_child_file_io(t_command *cmd);
void		ft_execute_child_cmd(t_command *cmd, t_data *data);
void		ft_close_parent_fds(t_command *cmd);
void		ft_close_pipes(int **pipes, int pipe_count);
int			ft_wait_children(pid_t *pids, int cmd_count);

// Environment utilities
char		**env_to_str_array(t_env *env);
int			ft_setup_redirections(t_command *cmd);

// Additional parsing helpers
int			handle_new_command_creation(t_token *token, t_parse_ctx *ctx);
int			process_single_token(t_token *current, t_parse_state *state);
int			finalize_last_command(t_command *current_cmd, t_data *data);
int			handle_pipe_token(t_command **current_cmd, t_data *data);
int			handle_redirection_token(t_parse_state *state, t_token *current);
int			handle_word_token_main(t_parse_state *state, t_token *current);

// Additional execution helpers
int			setup_heredoc_with_content(t_exec_params *params, int pipe_fds[2]);
int			setup_heredoc_empty(t_exec_params *params, int pipe_fds[2]);
int			setup_signal_handling(struct sigaction *sa_ignore,
				struct sigaction *sa_oldint, struct sigaction *sa_oldquit);
int			handle_child_process(t_exec_params *params);
int			cleanup_parent_process(t_exec_params *params, pid_t pid,
				struct sigaction sa_oldint, struct sigaction sa_oldquit);
void		handle_file_not_found(t_command *cmd, char **envp, t_data *data);
void		handle_permission_denied(t_command *cmd, char **envp, t_data *data);

// Redirection helpers
int			check_command_in_list(t_command *cmd, t_data *data);
void		add_command_to_list(t_command *cmd, t_data *data);
void		remove_command_from_list(t_command *cmd, t_data *data);
int			manage_command_in_list(t_command *cmd, t_data *data, int add);
int			allocate_heredoc_strings(t_command *cmd, char *delim);
int			setup_heredoc_content(t_command *cmd, char *content, char *delim);
void		cleanup_existing_heredoc(t_command *cmd);

#endif
