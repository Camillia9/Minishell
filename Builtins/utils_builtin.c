/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 15:33:49 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_name(char *var)
{
	int	i;

	if (!var || !var[0])
		return (0);
	if (var[0] != '_' && !ft_isalpha(var[0]))
		return (0);
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (var[i] != '_' && !ft_isalnum(var[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	sort_env_tab(char **sorted_env, int count)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(sorted_env[j], sorted_env[j + 1]) > 0)
			{
				tmp = sorted_env[j];
				sorted_env[j] = sorted_env[j + 1];
				sorted_env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_export_format(char *var)
{
	char	*equal_sign;

	equal_sign = ft_strchr(var, '=');
	if (equal_sign)
	{
		write(STDOUT_FILENO, "declare -x ", 12);
		write(STDOUT_FILENO, var, equal_sign - var + 1);
		write(STDOUT_FILENO, "\"", 1);
		write(STDOUT_FILENO, equal_sign + 1, ft_strlen(equal_sign + 1));
		write(STDOUT_FILENO, "\"\n", 2);
	}
	else
	{
		write(STDOUT_FILENO, "declare -x", 11);
		write(STDOUT_FILENO, var, ft_strlen(var));
		write(STDOUT_FILENO, "\n", 1);
	}
}

int	print_sorted_env_list(t_env *env_list)
{
	char	**env_tab;
	int		count;
	int		i;

	env_tab = env_to_tab(env_list);
	if (!env_tab)
		return (1);
	count = 0;
	while (env_tab[count])
		count++;
	sort_env_tab(env_tab, count);
	i = 0;
	while (i < count)
	{
		print_export_format(env_tab[i]);
		i++;
	}
	i = 0;
	while (env_tab[i])
	{
		free(env_tab[i]);
		i++;
	}
	free(env_tab);
	return (0);
}
