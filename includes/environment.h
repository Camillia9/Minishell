/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:37:06 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "types.h"

// Environment management functions
void	init_env(t_data *data, char **envp);
void	process_env_entry(t_env **env_list, char *envp_entry);
void	add_env(t_env **env_list, char *name, char *value, int exported);
t_env	*env_find(t_env *env_list, char *name);
void	env_update(t_env *env_list, char *name, char *new_value);
void	env_remove(t_env **env_list, char *name);

// Environment conversion functions
char	**env_to_tab(t_env *env_list);

// Builtin functions
int		builtin_export(char **args, t_env *env_list);
int		builtin_unset(char **args, t_env **env_list);
int		builtin_env(char **args, t_env *env_list);
int		builtin_cd(char **args, t_env *env_list);
int		builtin_echo(char **args);
int		builtin_exit(char **args);
int		builtin_pwd(char **args);

// Builtin utilities
int		is_valid_var_name(char *var);
int		print_sorted_env_list(t_env *env_list);
int		is_builtin(char *cmd);
int		execute_builtin(char **args, t_env **env_list, int *exit_status);

// CD builtin helper functions
char	*get_home_path(t_env *env_list);
char	*get_oldpwd_path(t_env *env_list);
int		update_pwd_vars(t_env *env_list, char *old_dir);
char	*handle_tilde_path(char **args, t_env *env_list, int *need_free);
char	*get_target_path(char **args, t_env *env_list, int *need_free);

#endif
