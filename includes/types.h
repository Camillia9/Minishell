/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:50:23 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}						t_token_type;

typedef struct s_env
{
	char				*name;
	char				*value;
	int					exported;
	struct s_env		*next;
}						t_env;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	int					quoted_single;
	int					quoted_double;
	struct s_token		*next;
}						t_token;

typedef struct s_command
{
	bool				last_infile_heredoc;
	char				*name_cmd;
	char				**args;
	int					arg_count;
	char				*input_file;
	char				*output_file;
	char				*append_file;
	char				*heredoc_delim;
	char				*heredoc_content;
	int					input_fd;
	int					output_fd;
	struct s_command	*next;
}						t_command;

typedef struct s_data
{
	t_command			*commands;
	t_env				*env;
	t_token				*tokens;
	int					cmd_count;
	int					exit_status;
}						t_data;

typedef struct s_quotes
{
	int					in_single;
	int					in_double;
	int					has_single;
	int					has_double;
}						t_quotes;

typedef struct s_expand_ctx
{
	char				**expanded;
	t_data				*data;
	t_quotes			*quotes;
}						t_expand_ctx;

typedef struct s_parse_ctx
{
	int					expecting_target;
	t_token_type		last_redir_type;
	t_command			**current_cmd;
}						t_parse_ctx;

typedef struct s_parse_state
{
	t_command			**current_cmd;
	int					*expecting_target;
	t_token_type		*last_type;
	t_data				*data;
}						t_parse_state;

typedef struct s_exec_params
{
	t_data				*data;
	t_command			*cmd;
	int					input_fd;
	int					output_fd;
	int					index;
}						t_exec_params;

typedef struct s_pipeline_child_params
{
	t_data				*data;
	int					pipe_fd[2];
	int					prev_pipe_read;
	int					cmd_index;
	t_command			*cmd;
}						t_pipeline_child_params;

#endif
