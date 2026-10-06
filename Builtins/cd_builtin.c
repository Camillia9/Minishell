/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:37:06 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_chdir(char *path, int need_free)
{
	int	ret;

	ret = chdir(path);
	if (ret != 0)
	{
		perror("minishell: cd");
		if (need_free)
			free(path);
		return (1);
	}
	if (need_free)
		free(path);
	return (0);
}

int	builtin_cd(char **args, t_env *env_list)
{
	char	*path;
	char	current_dir[PATH_MAX];
	int		need_free;

	if (getcwd(current_dir, PATH_MAX) == NULL)
	{
		perror("minishell: cd");
		return (1);
	}
	path = get_target_path(args, env_list, &need_free);
	if (!path)
		return (1);
	if (execute_chdir(path, need_free) != 0)
		return (1);
	return (update_pwd_vars(env_list, current_dir));
}
