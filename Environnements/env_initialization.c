/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_initialization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:34:54 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_env_entry(t_env **env_list, char *envp_entry)
{
	char	*equal_sign;
	char	*name;
	char	*value;
	int		name_len;

	equal_sign = ft_strchr(envp_entry, '=');
	if (equal_sign)
	{
		name_len = equal_sign - envp_entry;
		name = ft_substr(envp_entry, 0, name_len);
		value = ft_strdup(equal_sign + 1);
		add_env(env_list, name, value, 1);
		free(name);
		free(value);
	}
}

void	init_env(t_data *data, char **envp)
{
	t_env	*env_list;
	int		i;

	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		process_env_entry(&env_list, envp[i]);
		i++;
	}
	data->env = env_list;
}

void	add_env(t_env **env_list, char *name, char *value, int exported)
{
	t_env	*new_node;
	t_env	*current;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	new_node->exported = exported;
	new_node->next = NULL;
	if (*env_list == NULL)
	{
		*env_list = new_node;
		return ;
	}
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new_node;
}
