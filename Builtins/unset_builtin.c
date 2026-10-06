/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 15:37:59 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **args, t_env **env_list)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (args[i])
	{
		if (!is_valid_var_name(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			status = 1;
		}
		else
			env_remove(env_list, args[i]);
		i++;
	}
	return (status);
}
