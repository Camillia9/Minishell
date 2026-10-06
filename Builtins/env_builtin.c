/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 16:50:30 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **args, t_env *env_list)
{
	t_env	*current;

	(void)args;
	current = env_list;
	while (current)
	{
		if (current->exported)
		{
			ft_putstr_fd(current->name, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		current = current->next;
	}
	return (0);
}

int	builtin_env_test(char **args, t_env *env_list)
{
	char	**env_array;
	int		i;

	(void)args;
	env_array = env_to_tab(env_list);
	if (!env_array)
		return (1);
	i = 0;
	while (env_array[i])
	{
		ft_putstr_fd(env_array[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
	return (0);
}
