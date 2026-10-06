/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 15:37:57 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"));
}

int	execute_builtin(char **args, t_env **env_list, int *exit_status)
{
	int	ret;

	if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, *env_list));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd(args));
	else if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, *env_list));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, env_list));
	else if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(args, *env_list));
	else if (ft_strcmp(args[0], "exit") == 0)
	{
		ret = builtin_exit(args);
		if (ret != 1)
			*exit_status = ret;
		return (ret);
	}
	return (1);
}
