/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 15:33:49 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_with_value(t_env **env_list, char *arg)
{
	char	*equal_sign;
	char	*name;
	char	*value;
	t_env	*existing;

	equal_sign = ft_strchr(arg, '=');
	name = ft_substr(arg, 0, equal_sign - arg);
	value = ft_strdup(equal_sign + 1);
	existing = env_find(*env_list, name);
	if (existing)
	{
		env_update(*env_list, name, value);
		existing->exported = 1;
	}
	else
		add_env(env_list, name, value, 1);
	free(name);
	free(value);
}

static void	export_without_value(t_env **env_list, char *name)
{
	t_env	*existing;

	existing = env_find(*env_list, name);
	if (existing)
		existing->exported = 1;
	else
		add_env(env_list, name, "", 1);
}

static int	error_message(char *arg)
{
	ft_putstr_fd("minishell: export: '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (1);
}

int	builtin_export(char **args, t_env *env_list)
{
	int		i;
	int		status;
	char	*equal_sign;

	if (!args[1])
		return (print_sorted_env_list(env_list));
	i = 1;
	status = 0;
	while (args[i])
	{
		if (!is_valid_var_name(args[i]))
			status = error_message(args[i]);
		else
		{
			equal_sign = ft_strchr(args[i], '=');
			if (equal_sign)
				export_with_value(&env_list, args[i]);
			else
				export_without_value(&env_list, args[i]);
		}
		i++;
	}
	return (status);
}
