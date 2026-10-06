/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 15:33:49 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(char **args)
{
	char	current_dir[PATH_MAX];

	(void)args;
	if (getcwd(current_dir, PATH_MAX) == NULL)
	{
		perror("minishell: pwd");
		return (1);
	}
	ft_putstr_fd(current_dir, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
