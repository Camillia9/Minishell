/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:16:14 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_exported(t_env *env_list)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env_list;
	while (current)
	{
		if (current->exported)
			count++;
		current = current->next;
	}
	return (count);
}

static char	*create_env_string(char *name, char *value)
{
	char	*env_str;
	int		name_len;
	int		value_len;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	env_str = (char *)malloc(name_len + value_len + 2);
	if (!env_str)
		return (NULL);
	ft_strcpy(env_str, name);
	ft_strcat(env_str, "=");
	ft_strcat(env_str, value);
	return (env_str);
}

static int	fill_env_tab(t_env *env_list, char **env_tab, int count)
{
	t_env	*current;
	int		i;

	current = env_list;
	i = 0;
	while (current && i < count)
	{
		if (current->exported)
		{
			env_tab[i] = create_env_string(current->name, current->value);
			if (!env_tab[i])
				return (-1);
			i++;
		}
		current = current->next;
	}
	env_tab[i] = NULL;
	return (0);
}

static void	free_env_tab(char **env_tab, int count)
{
	while (--count >= 0)
		free(env_tab[count]);
	free(env_tab);
}

char	**env_to_tab(t_env *env_list)
{
	char	**env_tab;
	int		count;
	int		result;

	count = count_exported(env_list);
	env_tab = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_tab)
		return (NULL);
	result = fill_env_tab(env_list, env_tab, count);
	if (result == -1)
	{
		free_env_tab(env_tab, count);
		return (NULL);
	}
	return (env_tab);
}
