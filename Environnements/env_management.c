/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:16:14 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_find(t_env *env_list, char *name)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	env_update(t_env *env_list, char *name, char *new_value)
{
	t_env	*var;

	var = env_find(env_list, name);
	if (var)
	{
		free(var->value);
		var->value = ft_strdup(new_value);
	}
}

static int	remove_first_node(t_env **env_list, char *name)
{
	t_env	*to_remove;

	if (ft_strcmp((*env_list)->name, name) == 0)
	{
		to_remove = *env_list;
		*env_list = (*env_list)->next;
		free(to_remove->name);
		free(to_remove->value);
		free(to_remove);
		return (1);
	}
	return (0);
}

void	env_remove(t_env **env_list, char *name)
{
	t_env	*current;
	t_env	*previous;

	if (!*env_list)
		return ;
	if (remove_first_node(env_list, name))
		return ;
	previous = *env_list;
	current = (*env_list)->next;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			previous->next = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}
