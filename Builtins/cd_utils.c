/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 16:42:24 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home_path(t_env *env_list)
{
	t_env	*home_var;

	home_var = env_find(env_list, "HOME");
	if (!home_var || !home_var->value)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (NULL);
	}
	return (home_var->value);
}

char	*get_oldpwd_path(t_env *env_list)
{
	t_env	*oldpwd_var;

	oldpwd_var = env_find(env_list, "OLDPWD");
	if (!oldpwd_var || !oldpwd_var->value)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		return (NULL);
	}
	ft_putendl_fd(oldpwd_var->value, STDOUT_FILENO);
	return (oldpwd_var->value);
}

int	update_pwd_vars(t_env *env_list, char *old_dir)
{
	char	new_dir[PATH_MAX];
	t_env	*pwd_var;
	t_env	*oldpwd_var;

	if (getcwd(new_dir, PATH_MAX) == NULL)
	{
		perror("minishell: cd");
		return (1);
	}
	pwd_var = env_find(env_list, "PWD");
	if (pwd_var)
		env_update(env_list, "PWD", new_dir);
	else
		add_env(&env_list, "PWD", new_dir, 1);
	oldpwd_var = env_find(env_list, "OLDPWD");
	if (oldpwd_var)
		env_update(env_list, "OLDPWD", old_dir);
	else
		add_env(&env_list, "OLDPWD", old_dir, 1);
	return (0);
}

char	*handle_tilde_path(char **args, t_env *env_list, int *need_free)
{
	char	*home;
	char	*path;

	home = get_home_path(env_list);
	if (!home)
		return (NULL);
	if (args[1][1] == '\0')
		return (home);
	if (args[1][1] == '/')
	{
		path = ft_strjoin(home, args[1] + 1);
		*need_free = 1;
		return (path);
	}
	return (args[1]);
}

char	*get_target_path(char **args, t_env *env_list, int *need_free)
{
	if (!args[1])
	{
		*need_free = 0;
		return (get_home_path(env_list));
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		*need_free = 0;
		return (get_oldpwd_path(env_list));
	}
	else if (args[1][0] == '~')
		return (handle_tilde_path(args, env_list, need_free));
	*need_free = 0;
	return (args[1]);
}
