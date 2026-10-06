/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:29:03 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_absolute_path(char *cmd)
{
	if (cmd[0] == '/' || ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "../",
			3) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return ((char *)1);
}

char	*search_in_paths(char **paths, char *cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		cmd_path = validate_cmd_path(paths[i], cmd);
		if (cmd_path)
		{
			free_tab(paths);
			return (cmd_path);
		}
		i++;
	}
	free_tab(paths);
	return (NULL);
}
