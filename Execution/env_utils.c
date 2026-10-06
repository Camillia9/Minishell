/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:16:14 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_exported_env(t_env *env)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->exported)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

static char	*create_env_string(char *name, char *value)
{
	int		len;
	char	*str;

	len = ft_strlen(name) + ft_strlen(value) + 2;
	str = malloc(len);
	if (!str)
		return (NULL);
	ft_strlcpy(str, name, len);
	ft_strlcat(str, "=", len);
	ft_strlcat(str, value, len);
	return (str);
}

char	**env_to_str_array(t_env *env)
{
	t_env	*tmp;
	char	**env_array;
	int		i;
	int		count;

	count = count_exported_env(env);
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		if (tmp->exported)
		{
			env_array[i] = create_env_string(tmp->name, tmp->value);
			if (!env_array[i++])
				return (NULL);
		}
		tmp = tmp->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
