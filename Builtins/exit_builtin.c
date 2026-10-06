/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 22:34:38 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(const char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	is_valid_number(const char *str)
{
	int	sign;

	if (!is_numeric(str))
		return (0);
	sign = 1;
	if (str[0] == '-')
		sign = -1;
	if (sign == 1 && ft_strlen(str) > 19)
		return (0);
	if (sign == -1 && ft_strlen(str) > 20)
		return (0);
	if (sign == 1 && ft_strlen(str) == 19)
	{
		if (ft_strncmp(str, "9223372036854775807", 19) > 0)
			return (0);
	}
	if (sign == -1 && ft_strlen(str) == 20)
	{
		if (ft_strncmp(str + 1, "9223372036854775808", 19) > 0)
			return (0);
	}
	return (1);
}

int	builtin_exit(char **args)
{
	int			exit_code;
	long long	value;

	exit_code = 0;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!args[1])
		exit(0);
	if (!is_valid_number(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(2);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	value = ft_atoll(args[1]);
	exit_code = (unsigned char)value;
	exit(exit_code);
}
