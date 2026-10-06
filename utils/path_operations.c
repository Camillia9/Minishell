/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 19:01:13 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path_env(t_env *env_list)
{
	t_env	*path_var;

	path_var = env_find(env_list, "PATH");
	if (!path_var)
		return (NULL);
	return (path_var->value);
}

char	*validate_cmd_path(char *base_path, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(base_path, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_cmd_path(char *cmd, t_env *env_list)
{
	char	*path_env;
	char	**paths;
	char	*absolute_check;

	if (!cmd)
		return (NULL);
	absolute_check = check_absolute_path(cmd);
	if (absolute_check != (char *)1)
		return (absolute_check);
	path_env = find_path_env(env_list);
	if (!path_env)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (search_in_paths(paths, cmd));
}
