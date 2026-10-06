/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:05 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:16:14 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell.h"

char	*ft_get_env_value(t_env *env, const char *var)
{
	t_env	*current;

	if (!env || !var)
		return ("");
	current = env;
	while (current)
	{
		if (ft_strcmp(current->name, var) == 0)
			return (current->value);
		current = current->next;
	}
	return ("");
}

char	*ft_expand_tilde(const char *str, t_data *data)
{
	char	*home;
	char	*result;

	if (!str || str[0] != '~')
		return (ft_strdup(str));
	home = ft_get_env_value(data->env, "HOME");
	if (!home || !*home)
		return (ft_strdup(str));
	if (str[1] == '\0')
		return (ft_strdup(home));
	if (str[1] == '/')
	{
		result = ft_strjoin(home, str + 1);
		if (!result)
			return (ft_strdup(str));
		return (result);
	}
	return (ft_strdup(str));
}

int	ft_process_exit_status(int *i, char **expanded, t_data *data)
{
	char	exit_status_str[12];

	(*i) += 2;
	ft_itoa_simple(get_exit_status(data), exit_status_str);
	*expanded = ft_join_strings(*expanded, exit_status_str, 0);
	if (*expanded != NULL)
		return (1);
	else
		return (0);
}

int	ft_process_variable(const char *value, int *i, char **expanded,
		t_data *data)
{
	char	*var_name;
	char	*env_val;

	if (value[*i + 1] == '?')
		return (ft_process_exit_status(i, expanded, data));
	var_name = ft_extract_varname(value, i);
	if (!var_name)
		return (0);
	env_val = ft_get_env_value(data->env, var_name);
	*expanded = ft_join_strings(*expanded, env_val, 0);
	free(var_name);
	if (*expanded != NULL)
		return (1);
	else
		return (0);
}
